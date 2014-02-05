// Copyright (c) 2014 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//

#include "libcef_dll/cpptoc/cookie_manager_cpptoc.h"
#include "libcef_dll/ctocpp/completion_callback_ctocpp.h"
#include "libcef_dll/ctocpp/cookie_visitor_ctocpp.h"
#include "libcef_dll/transfer_util.h"


// GLOBAL FUNCTIONS - Body may be edited by hand.

CEF_EXPORT cef_cookie_manager_t* cef_cookie_manager_get_global_manager() {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  CefRefPtr<CefCookieManager> _retval = CefCookieManager::GetGlobalManager();

  // Return type: refptr_same
  return CefCookieManagerCppToC::Wrap(_retval);
}

CEF_EXPORT cef_cookie_manager_t* cef_cookie_manager_create_manager(
    const cef_string_t* path, int persist_session_cookies) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Unverified params: path

  // Execute
  CefRefPtr<CefCookieManager> _retval = CefCookieManager::CreateManager(
      CefString(path),
      persist_session_cookies?true:false);

  // Return type: refptr_same
  return CefCookieManagerCppToC::Wrap(_retval);
}


// MEMBER FUNCTIONS - Body may be edited by hand.

void CEF_CALLBACK cookie_manager_set_supported_schemes(
    struct _cef_cookie_manager_t* self, cef_string_list_t schemes) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;
  // Verify param: schemes; type: string_vec_byref_const
  DCHECK(schemes);
  if (!schemes)
    return;

  // Translate param: schemes; type: string_vec_byref_const
  std::vector<CefString> schemesList;
  transfer_string_list_contents(schemes, schemesList);

  // Execute
  CefCookieManagerCppToC::Get(self)->SetSupportedSchemes(
      schemesList);
}

int CEF_CALLBACK cookie_manager_visit_all_cookies(
    struct _cef_cookie_manager_t* self,
    struct _cef_cookie_visitor_t* visitor) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;
  // Verify param: visitor; type: refptr_diff
  DCHECK(visitor);
  if (!visitor)
    return 0;

  // Execute
  bool _retval = CefCookieManagerCppToC::Get(self)->VisitAllCookies(
      CefCookieVisitorCToCpp::Wrap(visitor));

  // Return type: bool
  return _retval;
}

int CEF_CALLBACK cookie_manager_visit_url_cookies(
    struct _cef_cookie_manager_t* self, const cef_string_t* url,
    int includeHttpOnly, struct _cef_cookie_visitor_t* visitor) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;
  // Verify param: url; type: string_byref_const
  DCHECK(url);
  if (!url)
    return 0;
  // Verify param: visitor; type: refptr_diff
  DCHECK(visitor);
  if (!visitor)
    return 0;

  // Execute
  bool _retval = CefCookieManagerCppToC::Get(self)->VisitUrlCookies(
      CefString(url),
      includeHttpOnly?true:false,
      CefCookieVisitorCToCpp::Wrap(visitor));

  // Return type: bool
  return _retval;
}

int CEF_CALLBACK cookie_manager_set_cookie(struct _cef_cookie_manager_t* self,
    const cef_string_t* url, const struct _cef_cookie_t* cookie) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;
  // Verify param: url; type: string_byref_const
  DCHECK(url);
  if (!url)
    return 0;
  // Verify param: cookie; type: struct_byref_const
  DCHECK(cookie);
  if (!cookie)
    return 0;

  // Translate param: cookie; type: struct_byref_const
  CefCookie cookieObj;
  if (cookie)
    cookieObj.Set(*cookie, false);

  // Execute
  bool _retval = CefCookieManagerCppToC::Get(self)->SetCookie(
      CefString(url),
      cookieObj);

  // Return type: bool
  return _retval;
}

int CEF_CALLBACK cookie_manager_delete_cookies(
    struct _cef_cookie_manager_t* self, const cef_string_t* url,
    const cef_string_t* cookie_name) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;
  // Unverified params: url, cookie_name

  // Execute
  bool _retval = CefCookieManagerCppToC::Get(self)->DeleteCookies(
      CefString(url),
      CefString(cookie_name));

  // Return type: bool
  return _retval;
}

int CEF_CALLBACK cookie_manager_set_storage_path(
    struct _cef_cookie_manager_t* self, const cef_string_t* path,
    int persist_session_cookies) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;
  // Unverified params: path

  // Execute
  bool _retval = CefCookieManagerCppToC::Get(self)->SetStoragePath(
      CefString(path),
      persist_session_cookies?true:false);

  // Return type: bool
  return _retval;
}

int CEF_CALLBACK cookie_manager_flush_store(struct _cef_cookie_manager_t* self,
    cef_completion_callback_t* callback) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;
  // Verify param: callback; type: refptr_diff
  DCHECK(callback);
  if (!callback)
    return 0;

  // Execute
  bool _retval = CefCookieManagerCppToC::Get(self)->FlushStore(
      CefCompletionCallbackCToCpp::Wrap(callback));

  // Return type: bool
  return _retval;
}


// CONSTRUCTOR - Do not edit by hand.

CefCookieManagerCppToC::CefCookieManagerCppToC(CefCookieManager* cls)
    : CefCppToC<CefCookieManagerCppToC, CefCookieManager, cef_cookie_manager_t>(
        cls) {
  struct_.struct_.set_supported_schemes = cookie_manager_set_supported_schemes;
  struct_.struct_.visit_all_cookies = cookie_manager_visit_all_cookies;
  struct_.struct_.visit_url_cookies = cookie_manager_visit_url_cookies;
  struct_.struct_.set_cookie = cookie_manager_set_cookie;
  struct_.struct_.delete_cookies = cookie_manager_delete_cookies;
  struct_.struct_.set_storage_path = cookie_manager_set_storage_path;
  struct_.struct_.flush_store = cookie_manager_flush_store;
}

#ifndef NDEBUG
template<> long CefCppToC<CefCookieManagerCppToC, CefCookieManager,
    cef_cookie_manager_t>::DebugObjCt = 0;
#endif

