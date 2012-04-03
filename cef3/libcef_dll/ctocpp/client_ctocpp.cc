// Copyright (c) 2012 The Chromium Embedded Framework Authors. All rights
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

#include "libcef_dll/cpptoc/browser_cpptoc.h"
#include "libcef_dll/cpptoc/process_message_cpptoc.h"
#include "libcef_dll/ctocpp/client_ctocpp.h"
#include "libcef_dll/ctocpp/display_handler_ctocpp.h"
#include "libcef_dll/ctocpp/geolocation_handler_ctocpp.h"
#include "libcef_dll/ctocpp/life_span_handler_ctocpp.h"
#include "libcef_dll/ctocpp/load_handler_ctocpp.h"
#include "libcef_dll/ctocpp/request_handler_ctocpp.h"


// VIRTUAL METHODS - Body may be edited by hand.

CefRefPtr<CefLifeSpanHandler> CefClientCToCpp::GetLifeSpanHandler() {
  if (CEF_MEMBER_MISSING(struct_, get_life_span_handler))
    return NULL;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_life_span_handler_t* _retval = struct_->get_life_span_handler(struct_);

  // Return type: refptr_same
  return CefLifeSpanHandlerCToCpp::Wrap(_retval);
}

CefRefPtr<CefLoadHandler> CefClientCToCpp::GetLoadHandler() {
  if (CEF_MEMBER_MISSING(struct_, get_load_handler))
    return NULL;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_load_handler_t* _retval = struct_->get_load_handler(struct_);

  // Return type: refptr_same
  return CefLoadHandlerCToCpp::Wrap(_retval);
}

CefRefPtr<CefRequestHandler> CefClientCToCpp::GetRequestHandler() {
  if (CEF_MEMBER_MISSING(struct_, get_request_handler))
    return NULL;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_request_handler_t* _retval = struct_->get_request_handler(struct_);

  // Return type: refptr_same
  return CefRequestHandlerCToCpp::Wrap(_retval);
}

CefRefPtr<CefDisplayHandler> CefClientCToCpp::GetDisplayHandler() {
  if (CEF_MEMBER_MISSING(struct_, get_display_handler))
    return NULL;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_display_handler_t* _retval = struct_->get_display_handler(struct_);

  // Return type: refptr_same
  return CefDisplayHandlerCToCpp::Wrap(_retval);
}

CefRefPtr<CefGeolocationHandler> CefClientCToCpp::GetGeolocationHandler() {
  if (CEF_MEMBER_MISSING(struct_, get_geolocation_handler))
    return NULL;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_geolocation_handler_t* _retval = struct_->get_geolocation_handler(
      struct_);

  // Return type: refptr_same
  return CefGeolocationHandlerCToCpp::Wrap(_retval);
}

bool CefClientCToCpp::OnProcessMessageRecieved(CefRefPtr<CefBrowser> browser,
    CefProcessId source_process, CefRefPtr<CefProcessMessage> message) {
  if (CEF_MEMBER_MISSING(struct_, on_process_message_recieved))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: browser; type: refptr_diff
  DCHECK(browser.get());
  if (!browser.get())
    return false;
  // Verify param: message; type: refptr_diff
  DCHECK(message.get());
  if (!message.get())
    return false;

  // Execute
  int _retval = struct_->on_process_message_recieved(struct_,
      CefBrowserCppToC::Wrap(browser),
      source_process,
      CefProcessMessageCppToC::Wrap(message));

  // Return type: bool
  return _retval?true:false;
}


#ifndef NDEBUG
template<> long CefCToCpp<CefClientCToCpp, CefClient,
    cef_client_t>::DebugObjCt = 0;
#endif

