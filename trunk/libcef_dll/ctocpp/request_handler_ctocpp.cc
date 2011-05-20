// Copyright (c) 2011 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// A portion of this file was generated by the CEF translator tool.  When
// making changes by hand only do so within the body of existing static and
// virtual method implementations. See the translator.README.txt file in the
// tools directory for more information.
//

#include "libcef_dll/cpptoc/browser_cpptoc.h"
#include "libcef_dll/cpptoc/frame_cpptoc.h"
#include "libcef_dll/cpptoc/request_cpptoc.h"
#include "libcef_dll/cpptoc/response_cpptoc.h"
#include "libcef_dll/cpptoc/stream_reader_cpptoc.h"
#include "libcef_dll/ctocpp/download_handler_ctocpp.h"
#include "libcef_dll/ctocpp/request_handler_ctocpp.h"


// VIRTUAL METHODS - Body may be edited by hand.

bool CefRequestHandlerCToCpp::OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, NavType navType,
    bool isRedirect)
{
  if (CEF_MEMBER_MISSING(struct_, on_before_browse))
    return true;

  return struct_->on_before_browse(struct_, CefBrowserCppToC::Wrap(browser),
      CefFrameCppToC::Wrap(frame), CefRequestCppToC::Wrap(request),
      navType, isRedirect) ? true : false;
}

bool CefRequestHandlerCToCpp::OnBeforeResourceLoad(
    CefRefPtr<CefBrowser> browser, CefRefPtr<CefRequest> request,
    CefString& redirectUrl, CefRefPtr<CefStreamReader>& resourceStream,
    CefRefPtr<CefResponse> response, int loadFlags)
{
  if (CEF_MEMBER_MISSING(struct_, on_before_resource_load))
    return false;

  cef_stream_reader_t* streamRet = NULL;

  int rv = struct_->on_before_resource_load(struct_,
      CefBrowserCppToC::Wrap(browser), CefRequestCppToC::Wrap(request),
      redirectUrl.GetWritableStruct(), &streamRet,
      CefResponseCppToC::Wrap(response), loadFlags);

  if(streamRet)
    resourceStream = CefStreamReaderCppToC::Unwrap(streamRet);

  return (rv ? true : false);
}

bool CefRequestHandlerCToCpp::OnProtocolExecution(CefRefPtr<CefBrowser> browser,
    const CefString& url, bool& allowOSExecution)
{
  if (CEF_MEMBER_MISSING(struct_, on_protocol_execution))
    return false;

  int allowExec = allowOSExecution;
  int rv = struct_->on_protocol_execution(struct_,
      CefBrowserCppToC::Wrap(browser), url.GetStruct(), &allowExec);
  allowOSExecution = allowExec?true:false;
  return (rv ? true : false);
}

bool CefRequestHandlerCToCpp::GetDownloadHandler(CefRefPtr<CefBrowser> browser,
    const CefString& mimeType, const CefString& fileName, int64 contentLength,
    CefRefPtr<CefDownloadHandler>& handler)
{
  if (CEF_MEMBER_MISSING(struct_, get_download_handler))
    return false;

  cef_download_handler_t* handlerRet = NULL;

  int rv = struct_->get_download_handler(struct_,
      CefBrowserCppToC::Wrap(browser), mimeType.GetStruct(),
      fileName.GetStruct(), contentLength, &handlerRet);

  if(handlerRet)
    handler = CefDownloadHandlerCToCpp::Wrap(handlerRet);

  return (rv ? true : false);
}

bool CefRequestHandlerCToCpp::GetAuthCredentials(CefRefPtr<CefBrowser> browser,
    bool isProxy, const CefString& host, const CefString& realm,
    const CefString& scheme, CefString& username, CefString& password)
{
  if (CEF_MEMBER_MISSING(struct_, get_auth_credentials))
    return false;

  return struct_->get_auth_credentials(struct_, CefBrowserCppToC::Wrap(browser),
      isProxy, host.GetStruct(), realm.GetStruct(), scheme.GetStruct(),
      username.GetWritableStruct(), password.GetWritableStruct()) ?
      true : false;
}


#ifndef NDEBUG
template<> long CefCToCpp<CefRequestHandlerCToCpp, CefRequestHandler,
    cef_request_handler_t>::DebugObjCt = 0;
#endif

