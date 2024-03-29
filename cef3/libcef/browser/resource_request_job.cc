// Copyright (c) 2012 The Chromium Embedded Framework Authors.
// Portions copyright (c) 2006-2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "libcef/browser/resource_request_job.h"

#include <map>
#include <vector>

#include "include/cef_callback.h"
#include "libcef/browser/cookie_manager_impl.h"
#include "libcef/browser/thread_util.h"
#include "libcef/common/request_impl.h"
#include "libcef/common/response_impl.h"

#include "base/logging.h"
#include "net/base/io_buffer.h"
#include "net/base/load_flags.h"
#include "net/http/http_response_headers.h"
#include "net/url_request/http_user_agent_settings.h"
#include "net/url_request/url_request.h"
#include "net/url_request/url_request_context.h"

using net::URLRequestStatus;

namespace {

bool SetHeaderIfMissing(CefRequest::HeaderMap& headerMap,
                        const std::string& name,
                        const std::string& value) {
  if (value.empty())
    return false;
                              
  CefRequest::HeaderMap::const_iterator it = headerMap.find(name);
  if (it == headerMap.end()) {
    headerMap.insert(std::make_pair(name, value));
    return true;
  }

  return false;
}

}  // namespace

// Client callback for asynchronous response continuation.
class CefResourceRequestJobCallback : public CefCallback {
 public:
  enum Type {
    HEADERS_AVAILABLE,
    BYTES_AVAILABLE,
  };

  explicit CefResourceRequestJobCallback(CefResourceRequestJob* job, Type type)
      : job_(job),
        type_(type),
        dest_(NULL),
        dest_size_(0) {}

  void Continue() override {
    // Continue asynchronously.
    CEF_POST_TASK(CEF_IOT,
        base::Bind(&CefResourceRequestJobCallback::ContinueOnIOThread, this));
  }

  void Cancel() override {
    // Cancel asynchronously.
    CEF_POST_TASK(CEF_IOT,
        base::Bind(&CefResourceRequestJobCallback::CancelOnIOThread, this));
  }

  void Detach() {
    CEF_REQUIRE_IOT();
    job_ = NULL;
  }

  void SetDestination(net::IOBuffer* dest, int dest_size) {
    CEF_REQUIRE_IOT();
    // Should not be called multiple times while IO is pending.
    DCHECK(!dest_);

    dest_ = dest;
    dest_size_ = dest_size;
  }

 private:
  void ContinueOnIOThread() {
    CEF_REQUIRE_IOT();

    // Return early if the callback has already been detached.
    if (!job_)
      return;

    if (type_ == HEADERS_AVAILABLE) {
      // Callback for headers available.
      if (!job_->has_response_started()) {
        // Send header information.
        job_->SendHeaders();
      }

      // This type of callback only ever needs to be called once.
      Detach();
    } else if (type_ == BYTES_AVAILABLE) {
      // Callback for bytes available.
      if (job_->has_response_started() &&
          job_->GetStatus().is_io_pending()) {
        // Read the bytes. They should be available but, if not, wait again.
        int bytes_read = 0;
        if (job_->ReadRawData(dest_, dest_size_, &bytes_read)) {
          // Must clear the members here because they may be reset as a result
          // of calling NotifyReadComplete.
          dest_size_ = 0;
          dest_ = NULL;

          // Clear the IO_PENDING status.
          job_->SetStatus(URLRequestStatus());

          // Notify about the available bytes. If bytes_read > 0 then
          // ReadRawData may be called from URLRequest::Read. If bytes_read == 0
          // then Kill will be called from the URLRequest destructor.
          job_->NotifyReadComplete(bytes_read);
        } else if (!job_->GetStatus().is_io_pending()) {
          // Failed due to an error.
          NOTREACHED() <<
              "ReadRawData returned false without setting IO as pending";
          job_->NotifyDone(URLRequestStatus());
          Detach();
        }
      }
    }
  }

  void CancelOnIOThread() {
    CEF_REQUIRE_IOT();

    if (job_)
      job_->Kill();
  }

  CefResourceRequestJob* job_;
  Type type_;

  net::IOBuffer* dest_;
  int dest_size_;

  IMPLEMENT_REFCOUNTING(CefResourceRequestJobCallback);
};

CefResourceRequestJob::CefResourceRequestJob(
    net::URLRequest* request,
    net::NetworkDelegate* network_delegate,
    CefRefPtr<CefResourceHandler> handler)
    : net::URLRequestJob(request, network_delegate),
      handler_(handler),
      done_(false),
      remaining_bytes_(0),
      response_cookies_save_index_(0),
      weak_factory_(this) {
}

CefResourceRequestJob::~CefResourceRequestJob() {
}

void CefResourceRequestJob::Start() {
  CEF_REQUIRE_IOT();

  request_start_time_ = base::Time::Now();
  cef_request_ = CefRequest::Create();

  // Populate the request data.
  static_cast<CefRequestImpl*>(cef_request_.get())->Set(request_);

  // Add default headers if not already specified.
  const net::URLRequestContext* context = request_->context();
  if (context) {
    CefRequest::HeaderMap headerMap;
    cef_request_->GetHeaderMap(headerMap);
    bool changed = false;

    const net::HttpUserAgentSettings* ua_settings =
        context->http_user_agent_settings();
    if (ua_settings) {
      if (SetHeaderIfMissing(headerMap,
                             net::HttpRequestHeaders::kAcceptLanguage,
                             ua_settings->GetAcceptLanguage())) {
        changed = true;
      }

      if (SetHeaderIfMissing(headerMap,
                             net::HttpRequestHeaders::kUserAgent,
                             ua_settings->GetUserAgent())) {
        changed = true;
      }
    }

    if (changed)
      cef_request_->SetHeaderMap(headerMap);
  }

  AddCookieHeaderAndStart();
}

void CefResourceRequestJob::Kill() {
  CEF_REQUIRE_IOT();

  if (!done_) {
    // Notify the handler that the request has been canceled.
    handler_->Cancel();
  }

  if (callback_.get()) {
    callback_->Detach();
    callback_ = NULL;
  }

  net::URLRequestJob::Kill();
}

// This method will be called by URLRequestJob::Read and our callback.
// It can indicate the following states:
// 1. If the request is complete set |bytes_read| == 0 and return true. The
//    caller is then responsible for calling NotifyReadComplete. ReadRawData
//    should not be called again.
// 2. If data is available synchronously set |bytes_read| > 0 and return true.
//    The caller is then responsible for calling NotifyReadComplete. ReadRawData
//    may be called again by URLRequestJob::Read.
// 3. If data is not available now but may be available asynchronously set
//    status to IO_PENDING and return false. When executed asynchronously the
//    callback will again call ReadRawData. If data is returned at that time the
//    callback will clear the status and call NotifyReadComplete.
bool CefResourceRequestJob::ReadRawData(net::IOBuffer* dest, int dest_size,
                                        int* bytes_read) {
  CEF_REQUIRE_IOT();

  DCHECK_NE(dest_size, 0);
  DCHECK(bytes_read);

  if (remaining_bytes_ == 0) {
    // No more data to read.
    *bytes_read = 0;
    done_ = true;
    return true;
  } else if (remaining_bytes_ > 0 && remaining_bytes_ < dest_size) {
    // The handler knows the content size beforehand.
    dest_size = static_cast<int>(remaining_bytes_);
  }

  if (!callback_.get()) {
    // Create the bytes available callback that will be used until the request
    // is completed.
    callback_ = new CefResourceRequestJobCallback(this,
        CefResourceRequestJobCallback::BYTES_AVAILABLE);
  }

  // Read response data from the handler.
  bool rv = handler_->ReadResponse(dest->data(), dest_size, *bytes_read,
                                   callback_.get());
  if (!rv) {
    // The handler has indicated completion of the request.
    *bytes_read = 0;
    done_ = true;
    return true;
  } else if (*bytes_read == 0) {
    // Continue reading asynchronously. May happen multiple times in a row so
    // only set IO pending the first time.
    if (!GetStatus().is_io_pending()) {
      SetStatus(URLRequestStatus(URLRequestStatus::IO_PENDING, 0));
      callback_->SetDestination(dest, dest_size);
    }
    return false;
  } else if (*bytes_read > dest_size) {
    // Normalize the return value.
    *bytes_read = dest_size;
  }

  if (remaining_bytes_ > 0)
    remaining_bytes_ -= *bytes_read;

  // Continue calling this method.
  return true;
}

void CefResourceRequestJob::GetResponseInfo(net::HttpResponseInfo* info) {
  CEF_REQUIRE_IOT();

  info->headers = GetResponseHeaders();
}

void CefResourceRequestJob::GetLoadTimingInfo(
    net::LoadTimingInfo* load_timing_info) const {
  // If haven't made it far enough to receive any headers, don't return
  // anything. This makes for more consistent behavior in the case of errors.
  if (!response_.get() || receive_headers_end_.is_null())
    return;
  load_timing_info->request_start_time = request_start_time_;
  load_timing_info->receive_headers_end = receive_headers_end_;
}

bool CefResourceRequestJob::GetResponseCookies(
    std::vector<std::string>* cookies) {
  CEF_REQUIRE_IOT();

  cookies->clear();
  FetchResponseCookies(cookies);
  return true;
}

bool CefResourceRequestJob::IsRedirectResponse(GURL* location,
                                               int* http_status_code) {
  CEF_REQUIRE_IOT();

  if (redirect_url_.is_valid()) {
    // Redirect to the new URL.
    *http_status_code = 303;
    location->Swap(&redirect_url_);
    return true;
  }

  if (response_.get()) {
    // Check for HTTP 302 or HTTP 303 redirect.
    int status = response_->GetStatus();
    if (status == 302 || status == 303) {
      CefResponse::HeaderMap headerMap;
      response_->GetHeaderMap(headerMap);
      CefRequest::HeaderMap::iterator iter = headerMap.find("Location");
      if (iter != headerMap.end()) {
          GURL new_url = GURL(std::string(iter->second));
          *http_status_code = status;
          location->Swap(&new_url);
          return true;
      }
    }
  }

  return false;
}

bool CefResourceRequestJob::GetMimeType(std::string* mime_type) const {
  CEF_REQUIRE_IOT();

  if (response_.get())
    *mime_type = response_->GetMimeType();
  return true;
}

void CefResourceRequestJob::SendHeaders() {
  CEF_REQUIRE_IOT();

  // Clear the headers available callback.
  callback_ = NULL;

  // We may have been orphaned...
  if (!request())
    return;

  response_ = new CefResponseImpl();
  remaining_bytes_ = 0;

  CefString redirectUrl;

  // Get header information from the handler.
  handler_->GetResponseHeaders(response_, remaining_bytes_, redirectUrl);
  receive_headers_end_ = base::TimeTicks::Now();
  if (!redirectUrl.empty()) {
    std::string redirectUrlStr = redirectUrl;
    redirect_url_ = GURL(redirectUrlStr);
  }

  if (remaining_bytes_ > 0)
    set_expected_content_size(remaining_bytes_);

  // Continue processing the request.
  SaveCookiesAndNotifyHeadersComplete();
}

void CefResourceRequestJob::AddCookieHeaderAndStart() {
  // No matter what, we want to report our status as IO pending since we will
  // be notifying our consumer asynchronously via OnStartCompleted.
  SetStatus(URLRequestStatus(URLRequestStatus::IO_PENDING, 0));

  // If the request was destroyed, then there is no more work to do.
  if (!request_)
    return;

  net::CookieStore* cookie_store =
      request_->context()->cookie_store();
  if (cookie_store &&
      !(request_->load_flags() & net::LOAD_DO_NOT_SEND_COOKIES)) {
    net::CookieMonster* cookie_monster = cookie_store->GetCookieMonster();
    if (cookie_monster) {
      cookie_monster->GetAllCookiesForURLAsync(
          request_->url(),
          base::Bind(&CefResourceRequestJob::CheckCookiePolicyAndLoad,
                      weak_factory_.GetWeakPtr()));
    } else {
      DoLoadCookies();
    }
  } else {
    DoStartTransaction();
  }
}

void CefResourceRequestJob::DoLoadCookies() {
  net::CookieOptions options;
  options.set_include_httponly();
  request_->context()->cookie_store()->GetCookiesWithOptionsAsync(
      request_->url(), options,
      base::Bind(&CefResourceRequestJob::OnCookiesLoaded,
                 weak_factory_.GetWeakPtr()));
}

void CefResourceRequestJob::CheckCookiePolicyAndLoad(
    const net::CookieList& cookie_list) {
  bool can_get_cookies = CanGetCookies(cookie_list);
  if (can_get_cookies) {
    net::CookieList::const_iterator it = cookie_list.begin();
    for (; it != cookie_list.end(); ++it) {
      CefCookie cookie;
      if (!CefCookieManagerImpl::GetCefCookie(*it, cookie) ||
          !handler_->CanGetCookie(cookie)) {
        can_get_cookies = false;
        break;
      }
    }
  }

  if (can_get_cookies)
    DoLoadCookies();
  else
    DoStartTransaction();
}

void CefResourceRequestJob::OnCookiesLoaded(const std::string& cookie_line) {
  if (!cookie_line.empty()) {
    CefRequest::HeaderMap headerMap;
    cef_request_->GetHeaderMap(headerMap);
    headerMap.insert(
        std::make_pair(net::HttpRequestHeaders::kCookie, cookie_line));
    cef_request_->SetHeaderMap(headerMap);
  }
  DoStartTransaction();
}

void CefResourceRequestJob::DoStartTransaction() {
  // We may have been canceled while retrieving cookies.
  if (GetStatus().is_success()) {
    StartTransaction();
  } else {
    NotifyCanceled();
  }
}

void CefResourceRequestJob::StartTransaction() {
  // Create the callback that will be used to notify when header information is
  // available.
  callback_ = new CefResourceRequestJobCallback(this,
      CefResourceRequestJobCallback::HEADERS_AVAILABLE);

  // Protect against deletion of this object.
  base::WeakPtr<CefResourceRequestJob> weak_ptr(weak_factory_.GetWeakPtr());

  // Handler can decide whether to process the request.
  bool rv = handler_->ProcessRequest(cef_request_, callback_.get());
  if (weak_ptr.get() && !rv) {
    // Cancel the request.
    NotifyCanceled();
  }
}

net::HttpResponseHeaders* CefResourceRequestJob::GetResponseHeaders() {
  DCHECK(response_.get());
  if (!response_headers_.get()) {
    CefResponseImpl* responseImpl =
        static_cast<CefResponseImpl*>(response_.get());
    response_headers_ = responseImpl->GetResponseHeaders();
  }
  return response_headers_.get();
}

void CefResourceRequestJob::SaveCookiesAndNotifyHeadersComplete() {
  if (request_->load_flags() & net::LOAD_DO_NOT_SAVE_COOKIES) {
    SetStatus(URLRequestStatus());  // Clear the IO_PENDING status
    NotifyHeadersComplete();
    return;
  }

  response_cookies_.clear();
  response_cookies_save_index_ = 0;

  FetchResponseCookies(&response_cookies_);

  // Now, loop over the response cookies, and attempt to persist each.
  SaveNextCookie();
}

void CefResourceRequestJob::SaveNextCookie() {
  if (response_cookies_save_index_ == response_cookies_.size()) {
    response_cookies_.clear();
    response_cookies_save_index_ = 0;
    SetStatus(URLRequestStatus());  // Clear the IO_PENDING status
    NotifyHeadersComplete();
    return;
  }

  // No matter what, we want to report our status as IO pending since we will
  // be notifying our consumer asynchronously via OnStartCompleted.
  SetStatus(URLRequestStatus(URLRequestStatus::IO_PENDING, 0));

  net::CookieOptions options;
  options.set_include_httponly();
  bool can_set_cookie = CanSetCookie(
      response_cookies_[response_cookies_save_index_], &options);
  if (can_set_cookie) {
    CefCookie cookie;
    if (CefCookieManagerImpl::GetCefCookie(request_->url(),
            response_cookies_[response_cookies_save_index_], cookie)) {
      can_set_cookie = handler_->CanSetCookie(cookie);
    } else {
      can_set_cookie = false;
    }
  }

  if (can_set_cookie) {
    request_->context()->cookie_store()->SetCookieWithOptionsAsync(
        request_->url(), response_cookies_[response_cookies_save_index_],
        options, base::Bind(&CefResourceRequestJob::OnCookieSaved,
                            weak_factory_.GetWeakPtr()));
    return;
  }

  CookieHandled();
}

void CefResourceRequestJob::OnCookieSaved(bool cookie_status) {
  CookieHandled();
}

void CefResourceRequestJob::CookieHandled() {
  response_cookies_save_index_++;
  // We may have been canceled within OnSetCookie.
  if (GetStatus().is_success()) {
    SaveNextCookie();
  } else {
    NotifyCanceled();
  }
}

void CefResourceRequestJob::FetchResponseCookies(
    std::vector<std::string>* cookies) {
  const std::string name = "Set-Cookie";
  std::string value;

  void* iter = NULL;
  net::HttpResponseHeaders* headers = GetResponseHeaders();
  while (headers->EnumerateHeader(&iter, name, &value)) {
    if (!value.empty())
      cookies->push_back(value);
  }
}
