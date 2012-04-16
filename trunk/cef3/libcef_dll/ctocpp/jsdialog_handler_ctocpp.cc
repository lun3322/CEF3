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
#include "libcef_dll/cpptoc/jsdialog_callback_cpptoc.h"
#include "libcef_dll/ctocpp/jsdialog_handler_ctocpp.h"


// VIRTUAL METHODS - Body may be edited by hand.

bool CefJSDialogHandlerCToCpp::OnJSDialog(CefRefPtr<CefBrowser> browser,
    const CefString& origin_url, const CefString& accept_lang,
    JSDialogType dialog_type, const CefString& message_text,
    const CefString& default_prompt_text,
    CefRefPtr<CefJSDialogCallback> callback, bool& suppress_message) {
  if (CEF_MEMBER_MISSING(struct_, on_jsdialog))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: browser; type: refptr_diff
  DCHECK(browser.get());
  if (!browser.get())
    return false;
  // Verify param: origin_url; type: string_byref_const
  DCHECK(!origin_url.empty());
  if (origin_url.empty())
    return false;
  // Verify param: callback; type: refptr_diff
  DCHECK(callback.get());
  if (!callback.get())
    return false;
  // Unverified params: accept_lang, message_text, default_prompt_text

  // Translate param: suppress_message; type: bool_byref
  int suppress_messageInt = suppress_message;

  // Execute
  int _retval = struct_->on_jsdialog(struct_,
      CefBrowserCppToC::Wrap(browser),
      origin_url.GetStruct(),
      accept_lang.GetStruct(),
      dialog_type,
      message_text.GetStruct(),
      default_prompt_text.GetStruct(),
      CefJSDialogCallbackCppToC::Wrap(callback),
      &suppress_messageInt);

  // Restore param:suppress_message; type: bool_byref
  suppress_message = suppress_messageInt?true:false;

  // Return type: bool
  return _retval?true:false;
}

bool CefJSDialogHandlerCToCpp::OnBeforeUnloadDialog(
    CefRefPtr<CefBrowser> browser, const CefString& message_text,
    bool is_reload, CefRefPtr<CefJSDialogCallback> callback) {
  if (CEF_MEMBER_MISSING(struct_, on_before_unload_dialog))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: browser; type: refptr_diff
  DCHECK(browser.get());
  if (!browser.get())
    return false;
  // Verify param: callback; type: refptr_diff
  DCHECK(callback.get());
  if (!callback.get())
    return false;
  // Unverified params: message_text

  // Execute
  int _retval = struct_->on_before_unload_dialog(struct_,
      CefBrowserCppToC::Wrap(browser),
      message_text.GetStruct(),
      is_reload,
      CefJSDialogCallbackCppToC::Wrap(callback));

  // Return type: bool
  return _retval?true:false;
}

void CefJSDialogHandlerCToCpp::OnResetDialogState(
    CefRefPtr<CefBrowser> browser) {
  if (CEF_MEMBER_MISSING(struct_, on_reset_dialog_state))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: browser; type: refptr_diff
  DCHECK(browser.get());
  if (!browser.get())
    return;

  // Execute
  struct_->on_reset_dialog_state(struct_,
      CefBrowserCppToC::Wrap(browser));
}


#ifndef NDEBUG
template<> long CefCToCpp<CefJSDialogHandlerCToCpp, CefJSDialogHandler,
    cef_jsdialog_handler_t>::DebugObjCt = 0;
#endif

