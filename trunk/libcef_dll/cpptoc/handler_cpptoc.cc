// Copyright (c) 2010 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// A portion of this file was generated by the CEF translator tool.  When
// making changes by hand only do so within the body of existing function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//

#include "libcef_dll/cpptoc/download_handler_cpptoc.h"
#include "libcef_dll/cpptoc/handler_cpptoc.h"
#include "libcef_dll/ctocpp/browser_ctocpp.h"
#include "libcef_dll/ctocpp/frame_ctocpp.h"
#include "libcef_dll/ctocpp/request_ctocpp.h"
#include "libcef_dll/ctocpp/stream_reader_ctocpp.h"
#include "libcef_dll/ctocpp/v8value_ctocpp.h"


// MEMBER FUNCTIONS - Body may be edited by hand.

enum cef_retval_t CEF_CALLBACK handler_handle_before_created(
    struct _cef_handler_t* self, cef_browser_t* parentBrowser,
    cef_window_info_t* windowInfo, int popup,
    const struct _cef_popup_features_t* popupFeatures,
    struct _cef_handler_t** handler, cef_string_t* url,
    struct _cef_browser_settings_t* settings)
{
  DCHECK(self);
  DCHECK(windowInfo);
  DCHECK(handler && *handler);
  DCHECK(url);
  if(!self || !windowInfo || !handler || !*handler || !url)
    return RV_CONTINUE;

  CefWindowInfo wndInfo;
  CefBrowserSettings browserSettings;
  CefPopupFeatures features;
  
  // Take ownership of the values.
  wndInfo.AttachTo(*windowInfo);
  browserSettings.AttachTo(*settings);
  
  // Reference the existing values instead of copying.
  features.Set(*popupFeatures, false);
  
  // |newHandler| will start off pointing to the current handler.
  CefRefPtr<CefHandler> handlerPtr = CefHandlerCppToC::Unwrap(*handler);
  CefHandler* origHandler = handlerPtr.get();
  
  // |parentBrowser| will be NULL if this is a top-level browser window.
  CefRefPtr<CefBrowser> browserPtr;
  if(parentBrowser)
    browserPtr = CefBrowserCToCpp::Wrap(parentBrowser);
  
  CefString urlStr(url);
  enum cef_retval_t rv = CefHandlerCppToC::Get(self)->HandleBeforeCreated(
      browserPtr, wndInfo, popup?true:false, features, handlerPtr,
      urlStr, browserSettings);

 if(handlerPtr.get() != origHandler) {
    // The handler has been changed.
    *handler = CefHandlerCppToC::Wrap(handlerPtr);
  }

  // Return the values to the structures.
  wndInfo.DetachTo(*windowInfo);
  browserSettings.DetachTo(*settings);

  return rv;
}

enum cef_retval_t CEF_CALLBACK handler_handle_after_created(
    struct _cef_handler_t* self, cef_browser_t* browser)
{
  DCHECK(self);
  DCHECK(browser);
  if(!self || !browser)
    return RV_CONTINUE;

  return CefHandlerCppToC::Get(self)->HandleAfterCreated(
      CefBrowserCToCpp::Wrap(browser));
}

enum cef_retval_t CEF_CALLBACK handler_handle_address_change(
    struct _cef_handler_t* self, cef_browser_t* browser, cef_frame_t* frame,
    const cef_string_t* url)
{
  DCHECK(self);
  DCHECK(browser);
  DCHECK(frame);
  if(!self || !browser || !frame)
    return RV_CONTINUE;

  return CefHandlerCppToC::Get(self)->HandleAddressChange(
      CefBrowserCToCpp::Wrap(browser), CefFrameCToCpp::Wrap(frame),
      CefString(url));
}

enum cef_retval_t CEF_CALLBACK handler_handle_title_change(
    struct _cef_handler_t* self, cef_browser_t* browser,
    const cef_string_t* title)
{
  DCHECK(self);
  DCHECK(browser);
  if(!self || !browser)
    return RV_CONTINUE;

  return CefHandlerCppToC::Get(self)->HandleTitleChange(
      CefBrowserCToCpp::Wrap(browser), CefString(title));
}

enum cef_retval_t CEF_CALLBACK handler_handle_nav_state_change(
    struct _cef_handler_t* self, cef_browser_t* browser, int canGoBack,
    int canGoForward)
{
  DCHECK(self);
  DCHECK(browser);
  if(!self || !browser)
    return RV_CONTINUE;

  return CefHandlerCppToC::Get(self)->HandleNavStateChange(
      CefBrowserCToCpp::Wrap(browser), (canGoBack?true:false),
      (canGoForward?true:false));
}

enum cef_retval_t CEF_CALLBACK handler_handle_before_browse(
    struct _cef_handler_t* self, cef_browser_t* browser, cef_frame_t* frame,
    struct _cef_request_t* request, enum cef_handler_navtype_t navType,
    int isRedirect)
{
  DCHECK(self);
  DCHECK(browser);
  DCHECK(frame);
  DCHECK(request);
  if(!self || !browser || !request || !frame)
    return RV_CONTINUE;

  return CefHandlerCppToC::Get(self)->HandleBeforeBrowse(
      CefBrowserCToCpp::Wrap(browser), CefFrameCToCpp::Wrap(frame),
      CefRequestCToCpp::Wrap(request), navType, (isRedirect ? true : false));
}

enum cef_retval_t CEF_CALLBACK handler_handle_load_start(
    struct _cef_handler_t* self, cef_browser_t* browser, cef_frame_t* frame)
{
  DCHECK(self);
  DCHECK(browser);
  if(!self || !browser)
    return RV_CONTINUE;

  CefRefPtr<CefFrame> framePtr;
  if(frame)
    framePtr = CefFrameCToCpp::Wrap(frame);

  return CefHandlerCppToC::Get(self)->HandleLoadStart(
      CefBrowserCToCpp::Wrap(browser), framePtr);
}

enum cef_retval_t CEF_CALLBACK handler_handle_load_end(
    struct _cef_handler_t* self, cef_browser_t* browser, cef_frame_t* frame,
    int httpStatusCode)
{
  DCHECK(self);
  DCHECK(browser);
  if(!self || !browser)
    return RV_CONTINUE;

  CefRefPtr<CefFrame> framePtr;
  if(frame)
    framePtr = CefFrameCToCpp::Wrap(frame);

  return CefHandlerCppToC::Get(self)->HandleLoadEnd(
      CefBrowserCToCpp::Wrap(browser), framePtr, httpStatusCode);
}

enum cef_retval_t CEF_CALLBACK handler_handle_load_error(
    struct _cef_handler_t* self, cef_browser_t* browser, cef_frame_t* frame,
    enum cef_handler_errorcode_t errorCode, const cef_string_t* failedUrl,
    cef_string_t* errorText)
{
  DCHECK(self);
  DCHECK(browser);
  DCHECK(frame);
  DCHECK(errorText);
  if(!self || !browser || !errorText || !frame)
    return RV_CONTINUE;

  CefString errorTextStr(errorText);
  return CefHandlerCppToC::Get(self)->HandleLoadError(
      CefBrowserCToCpp::Wrap(browser), CefFrameCToCpp::Wrap(frame), errorCode,
      CefString(failedUrl), errorTextStr);
}

enum cef_retval_t CEF_CALLBACK handler_handle_before_resource_load(
    struct _cef_handler_t* self, cef_browser_t* browser,
    struct _cef_request_t* request, cef_string_t* redirectUrl,
    struct _cef_stream_reader_t** resourceStream, cef_string_t* mimeType,
    int loadFlags)
{
  DCHECK(self);
  DCHECK(browser);
  DCHECK(redirectUrl);
  DCHECK(resourceStream);
  DCHECK(mimeType);
  if(!self || !browser || !redirectUrl || !resourceStream || !mimeType)
    return RV_CONTINUE;

  CefRefPtr<CefStreamReader> streamPtr;

  CefString redirectUrlStr(redirectUrl);
  CefString mimeTypeStr(mimeType);
  enum cef_retval_t rv = CefHandlerCppToC::Get(self)->
      HandleBeforeResourceLoad(CefBrowserCToCpp::Wrap(browser),
      CefRequestCToCpp::Wrap(request), redirectUrlStr, streamPtr, mimeTypeStr,
      loadFlags);

  if(streamPtr.get())
    *resourceStream = CefStreamReaderCToCpp::Unwrap(streamPtr);

  return rv;
}

enum cef_retval_t CEF_CALLBACK handler_handle_protocol_execution(
    struct _cef_handler_t* self, cef_browser_t* browser,
    const cef_string_t* url, int* allow_os_execution)
{
  DCHECK(self);
  DCHECK(browser);
  if(!self || !browser)
    return RV_CONTINUE;

  bool allowExec = *allow_os_execution?true:false;
  enum cef_retval_t rv = CefHandlerCppToC::Get(self)->HandleProtocolExecution(
      CefBrowserCToCpp::Wrap(browser), CefString(url), allowExec);
  *allow_os_execution = allowExec;
  return rv;
}

enum cef_retval_t CEF_CALLBACK handler_handle_download_response(
    struct _cef_handler_t* self, cef_browser_t* browser,
    const cef_string_t* mimeType, const cef_string_t* fileName,
    int64 contentLength, struct _cef_download_handler_t** handler)
{
  DCHECK(self);
  DCHECK(browser);
  DCHECK(mimeType);
  DCHECK(fileName);
  if(!self || !browser || !mimeType || !fileName)
    return RV_CONTINUE;

  CefRefPtr<CefDownloadHandler> downloadPtr;

  enum cef_retval_t rv = CefHandlerCppToC::Get(self)->
      HandleDownloadResponse(CefBrowserCToCpp::Wrap(browser),
      CefString(mimeType), CefString(fileName), contentLength, downloadPtr);

  if(downloadPtr.get())
    *handler = CefDownloadHandlerCppToC::Wrap(downloadPtr);

  return rv;
}

enum cef_retval_t CEF_CALLBACK handler_handle_authentication_request(
    struct _cef_handler_t* self, cef_browser_t* browser, int isProxy,
    const cef_string_t* host, const cef_string_t* realm,
    const cef_string_t* scheme, cef_string_t* username,
    cef_string_t* password)
{
  DCHECK(self);
  DCHECK(browser);
  DCHECK(username && password);
  if (!self || !browser || !username || !password)
    return RV_CONTINUE;

  CefString usernameStr(username);
  CefString passwordStr(password);

  return CefHandlerCppToC::Get(self)->
      HandleAuthenticationRequest(CefBrowserCToCpp::Wrap(browser),
      (isProxy ? true : false), CefString(host), CefString(realm),
      CefString(scheme), usernameStr, passwordStr);
}

enum cef_retval_t CEF_CALLBACK handler_handle_before_menu(
    struct _cef_handler_t* self, cef_browser_t* browser,
    const cef_handler_menuinfo_t* menuInfo)
{
  DCHECK(self);
  DCHECK(browser);
  DCHECK(menuInfo);
  if(!self || !browser || !menuInfo)
    return RV_CONTINUE;

  return CefHandlerCppToC::Get(self)->HandleBeforeMenu(
      CefBrowserCToCpp::Wrap(browser), *menuInfo);
}

enum cef_retval_t CEF_CALLBACK handler_handle_get_menu_label(
    struct _cef_handler_t* self, cef_browser_t* browser,
    enum cef_handler_menuid_t menuId, cef_string_t* label)
{
  DCHECK(self);
  DCHECK(browser);
  DCHECK(label);
  if(!self || !browser || !label)
    return RV_CONTINUE;

  CefString labelStr(label);
  return CefHandlerCppToC::Get(self)->HandleGetMenuLabel(
      CefBrowserCToCpp::Wrap(browser), menuId, labelStr);
}

enum cef_retval_t CEF_CALLBACK handler_handle_menu_action(
    struct _cef_handler_t* self, cef_browser_t* browser,
    enum cef_handler_menuid_t menuId)
{
  DCHECK(self);
  DCHECK(browser);
  if(!self || !browser)
    return RV_CONTINUE;

  return CefHandlerCppToC::Get(self)->HandleMenuAction(
      CefBrowserCToCpp::Wrap(browser), menuId);
}

enum cef_retval_t CEF_CALLBACK handler_handle_print_options(
    struct _cef_handler_t* self, cef_browser_t* browser,
    struct _cef_print_options_t* printOptions)
{
  DCHECK(self);
  DCHECK(browser);
  DCHECK(printOptions);
  if(!self || !browser || !printOptions)
    return RV_CONTINUE;

  return CefHandlerCppToC::Get(self)->HandlePrintOptions(CefBrowserCToCpp::Wrap(browser), *printOptions);
}

enum cef_retval_t CEF_CALLBACK handler_handle_print_header_footer(
    struct _cef_handler_t* self, cef_browser_t* browser, cef_frame_t* frame,
    cef_print_info_t* printInfo, const cef_string_t* url,
    const cef_string_t* title, int currentPage, int maxPages,
    cef_string_t* topLeft, cef_string_t* topCenter, cef_string_t* topRight,
    cef_string_t* bottomLeft, cef_string_t* bottomCenter,
    cef_string_t* bottomRight)
{
  DCHECK(self);
  DCHECK(browser);
  DCHECK(frame);
  DCHECK(printInfo);
  DCHECK(topLeft && topCenter && topRight);
  DCHECK(bottomLeft && bottomCenter && bottomRight);
  if(!self || !browser || !frame || !printInfo || !topLeft || !topCenter
      || !topRight || !bottomLeft || !bottomCenter || !bottomRight)
    return RV_CONTINUE;

  CefPrintInfo info = *printInfo;

  CefString topLeftStr(topLeft);
  CefString topCenterStr(topCenter);
  CefString topRightStr(topRight);
  CefString bottomLeftStr(bottomLeft);
  CefString bottomCenterStr(bottomCenter);
  CefString bottomRightStr(bottomRight);
  return CefHandlerCppToC::Get(self)->
      HandlePrintHeaderFooter(CefBrowserCToCpp::Wrap(browser),
      CefFrameCToCpp::Wrap(frame), info, CefString(url), CefString(title),
      currentPage, maxPages, topLeftStr, topCenterStr, topRightStr,
      bottomLeftStr, bottomCenterStr, bottomRightStr);
}

enum cef_retval_t CEF_CALLBACK handler_handle_jsalert(
    struct _cef_handler_t* self, cef_browser_t* browser, cef_frame_t* frame,
    const cef_string_t* message)
{
  DCHECK(self);
  DCHECK(browser);
  DCHECK(frame);
  if(!self || !browser || !frame)
    return RV_CONTINUE;

  return CefHandlerCppToC::Get(self)->HandleJSAlert(
      CefBrowserCToCpp::Wrap(browser), CefFrameCToCpp::Wrap(frame),
      CefString(message));
}

enum cef_retval_t CEF_CALLBACK handler_handle_jsconfirm(
    struct _cef_handler_t* self, cef_browser_t* browser, cef_frame_t* frame,
    const cef_string_t* message, int* retval)
{
  DCHECK(self);
  DCHECK(browser);
  DCHECK(frame);
  DCHECK(retval);
  if(!self || !browser || !retval || !frame)
    return RV_CONTINUE;

  bool ret = false;
  enum cef_retval_t rv = CefHandlerCppToC::Get(self)->HandleJSConfirm(
      CefBrowserCToCpp::Wrap(browser), CefFrameCToCpp::Wrap(frame),
      CefString(message), ret);
  *retval = (ret ? 1 : 0);

  return rv;
}

enum cef_retval_t CEF_CALLBACK handler_handle_jsprompt(
    struct _cef_handler_t* self, cef_browser_t* browser, cef_frame_t* frame,
    const cef_string_t* message, const cef_string_t* defaultValue, int* retval,
    cef_string_t* result)
{
  DCHECK(self);
  DCHECK(browser);
  DCHECK(frame);
  DCHECK(retval);
  DCHECK(result);
  if(!self || !browser || !frame || !retval || !result)
    return RV_CONTINUE;

  bool ret = false;
  CefString resultStr(result);
  enum cef_retval_t rv = CefHandlerCppToC::Get(self)->HandleJSPrompt(
      CefBrowserCToCpp::Wrap(browser), CefFrameCToCpp::Wrap(frame),
      CefString(message), CefString(defaultValue), ret, resultStr);
  *retval = (ret ? 1 : 0);

  return rv;
}

enum cef_retval_t CEF_CALLBACK handler_handle_jsbinding(
    struct _cef_handler_t* self, cef_browser_t* browser, cef_frame_t* frame,
    struct _cef_v8value_t* object)
{
  DCHECK(self);
  DCHECK(browser);
  DCHECK(frame);
  DCHECK(object);
  if(!self || !browser || !frame || !object)
    return RV_CONTINUE;

  return CefHandlerCppToC::Get(self)->HandleJSBinding(
      CefBrowserCToCpp::Wrap(browser), CefFrameCToCpp::Wrap(frame),
      CefV8ValueCToCpp::Wrap(object));
}

enum cef_retval_t CEF_CALLBACK handler_handle_before_window_close(
    struct _cef_handler_t* self, cef_browser_t* browser)
{
  DCHECK(self);
  DCHECK(browser);
  if(!self || !browser)
    return RV_CONTINUE;

  return CefHandlerCppToC::Get(self)->HandleBeforeWindowClose(
      CefBrowserCToCpp::Wrap(browser));
}

enum cef_retval_t CEF_CALLBACK handler_handle_take_focus(
    struct _cef_handler_t* self, cef_browser_t* browser, int reverse)
{
  DCHECK(self);
  DCHECK(browser);
  if(!self || !browser)
    return RV_CONTINUE;

  return CefHandlerCppToC::Get(self)->HandleTakeFocus(
      CefBrowserCToCpp::Wrap(browser), (reverse ? true : false));
}

enum cef_retval_t CEF_CALLBACK handler_handle_set_focus(
    struct _cef_handler_t* self, cef_browser_t* browser, int isWidget)
{
  DCHECK(self);
  DCHECK(browser);
  if(!self || !browser)
    return RV_CONTINUE;

  return CefHandlerCppToC::Get(self)->HandleSetFocus(
	  CefBrowserCToCpp::Wrap(browser), isWidget?true:false);
}

enum cef_retval_t CEF_CALLBACK handler_handle_key_event(
    struct _cef_handler_t* self, cef_browser_t* browser,
    enum cef_handler_keyevent_type_t type, int code, int modifiers,
    int isSystemKey)
{
  DCHECK(self);
  DCHECK(browser);
  if(!self || !browser)
    return RV_CONTINUE;

  return CefHandlerCppToC::Get(self)->HandleKeyEvent(
      CefBrowserCToCpp::Wrap(browser), type, code,
      modifiers, isSystemKey?true:false);
}

enum cef_retval_t CEF_CALLBACK handler_handle_tooltip(
    struct _cef_handler_t* self, cef_browser_t* browser, cef_string_t* text)
{
  DCHECK(self);
  DCHECK(browser);
  DCHECK(text);
  if(!self || !browser || !text)
    return RV_CONTINUE;

  CefString textStr(text);
  return CefHandlerCppToC::Get(self)->HandleTooltip(
      CefBrowserCToCpp::Wrap(browser), textStr);
}

enum cef_retval_t CEF_CALLBACK handler_handle_status(
    struct _cef_handler_t* self, cef_browser_t* browser,
    const cef_string_t* value, enum cef_handler_statustype_t type)
{
  DCHECK(self);
  DCHECK(browser);
  if(!self || !browser)
    return RV_CONTINUE;

  return CefHandlerCppToC::Get(self)->HandleStatus(
      CefBrowserCToCpp::Wrap(browser), CefString(value), type);
}

enum cef_retval_t CEF_CALLBACK handler_handle_console_message(
    struct _cef_handler_t* self, cef_browser_t* browser,
    const cef_string_t* message, const cef_string_t* source, int line)
{
  DCHECK(self);
  DCHECK(browser);
  if(!self || !browser)
    return RV_CONTINUE;

  return CefHandlerCppToC::Get(self)->HandleConsoleMessage(
      CefBrowserCToCpp::Wrap(browser), CefString(message), CefString(source),
      line);
}

enum cef_retval_t CEF_CALLBACK handler_handle_find_result(
    struct _cef_handler_t* self, cef_browser_t* browser, int identifier,
    int count, const cef_rect_t* selectionRect, int activeMatchOrdinal,
    int finalUpdate)
{
  DCHECK(self);
  DCHECK(browser);
  if(!self || !browser)
    return RV_CONTINUE;

  CefRect rect(*selectionRect);
  return CefHandlerCppToC::Get(self)->HandleFindResult(
      CefBrowserCToCpp::Wrap(browser), identifier, count, rect,
      activeMatchOrdinal, finalUpdate?true:false);
}

enum cef_retval_t CEF_CALLBACK handler_handle_get_rect(
    struct _cef_handler_t* self, cef_browser_t* browser, int screen,
    cef_rect_t* rect)
{
  DCHECK(self);
  DCHECK(browser);
  DCHECK(rect);
  if(!self || !browser || !rect)
    return RV_CONTINUE;

  CefRect changeRect(*rect);
  cef_retval_t rv = CefHandlerCppToC::Get(self)->HandleGetRect(
      CefBrowserCToCpp::Wrap(browser), screen?true:false, changeRect);
  *rect = changeRect;
  return rv;
}

enum cef_retval_t CEF_CALLBACK handler_handle_get_screen_point(
    struct _cef_handler_t* self, cef_browser_t* browser, int viewX, int viewY,
    int* screenX, int* screenY)
{
  DCHECK(self);
  DCHECK(browser);
  DCHECK(screenX);
  DCHECK(screenY);
  if(!self || !browser || !screenX || !screenY)
    return RV_CONTINUE;

  return CefHandlerCppToC::Get(self)->HandleGetScreenPoint(
      CefBrowserCToCpp::Wrap(browser), viewX, viewY, *screenX, *screenY);
}

enum cef_retval_t CEF_CALLBACK handler_handle_popup_change(
    struct _cef_handler_t* self, cef_browser_t* browser, int show,
    const cef_rect_t* rect)
{
  DCHECK(self);
  DCHECK(browser);
  DCHECK(rect);
  if(!self || !browser || !rect)
    return RV_CONTINUE;

  CefRect changeRect(*rect);
  return CefHandlerCppToC::Get(self)->HandlePopupChange(
      CefBrowserCToCpp::Wrap(browser), show?true:false, changeRect);
}

enum cef_retval_t CEF_CALLBACK handler_handle_paint(struct _cef_handler_t* self,
    cef_browser_t* browser, enum cef_paint_element_type_t type,
    const cef_rect_t* dirtyRect, const void* buffer)
{
  DCHECK(self);
  DCHECK(browser);
  DCHECK(dirtyRect);
  if(!self || !browser || !dirtyRect)
    return RV_CONTINUE;

  CefRect rect(*dirtyRect);
  return CefHandlerCppToC::Get(self)->HandlePaint(
      CefBrowserCToCpp::Wrap(browser), type, rect, buffer);
}

enum cef_retval_t CEF_CALLBACK handler_handle_cursor_change(
    struct _cef_handler_t* self, cef_browser_t* browser,
    cef_cursor_handle_t cursor)
{
  DCHECK(self);
  DCHECK(browser);
  if(!self || !browser)
    return RV_CONTINUE;

  return CefHandlerCppToC::Get(self)->HandleCursorChange(
      CefBrowserCToCpp::Wrap(browser), cursor);
}


// CONSTRUCTOR - Do not edit by hand.

CefHandlerCppToC::CefHandlerCppToC(CefHandler* cls)
    : CefCppToC<CefHandlerCppToC, CefHandler, cef_handler_t>(cls)
{
  struct_.struct_.handle_before_created = handler_handle_before_created;
  struct_.struct_.handle_after_created = handler_handle_after_created;
  struct_.struct_.handle_address_change = handler_handle_address_change;
  struct_.struct_.handle_title_change = handler_handle_title_change;
  struct_.struct_.handle_nav_state_change = handler_handle_nav_state_change;
  struct_.struct_.handle_before_browse = handler_handle_before_browse;
  struct_.struct_.handle_load_start = handler_handle_load_start;
  struct_.struct_.handle_load_end = handler_handle_load_end;
  struct_.struct_.handle_load_error = handler_handle_load_error;
  struct_.struct_.handle_before_resource_load =
      handler_handle_before_resource_load;
  struct_.struct_.handle_protocol_execution = handler_handle_protocol_execution;
  struct_.struct_.handle_download_response = handler_handle_download_response;
  struct_.struct_.handle_authentication_request =
      handler_handle_authentication_request;
  struct_.struct_.handle_before_menu = handler_handle_before_menu;
  struct_.struct_.handle_get_menu_label = handler_handle_get_menu_label;
  struct_.struct_.handle_menu_action = handler_handle_menu_action;
  struct_.struct_.handle_print_options = handler_handle_print_options;
  struct_.struct_.handle_print_header_footer =
      handler_handle_print_header_footer;
  struct_.struct_.handle_jsalert = handler_handle_jsalert;
  struct_.struct_.handle_jsconfirm = handler_handle_jsconfirm;
  struct_.struct_.handle_jsprompt = handler_handle_jsprompt;
  struct_.struct_.handle_jsbinding = handler_handle_jsbinding;
  struct_.struct_.handle_before_window_close =
      handler_handle_before_window_close;
  struct_.struct_.handle_take_focus = handler_handle_take_focus;
  struct_.struct_.handle_set_focus = handler_handle_set_focus;
  struct_.struct_.handle_key_event = handler_handle_key_event;
  struct_.struct_.handle_tooltip = handler_handle_tooltip;
  struct_.struct_.handle_status = handler_handle_status;
  struct_.struct_.handle_console_message = handler_handle_console_message;
  struct_.struct_.handle_find_result = handler_handle_find_result;
  struct_.struct_.handle_get_rect = handler_handle_get_rect;
  struct_.struct_.handle_get_screen_point = handler_handle_get_screen_point;
  struct_.struct_.handle_popup_change = handler_handle_popup_change;
  struct_.struct_.handle_paint = handler_handle_paint;
  struct_.struct_.handle_cursor_change = handler_handle_cursor_change;
}

#ifdef _DEBUG
template<> long CefCppToC<CefHandlerCppToC, CefHandler,
    cef_handler_t>::DebugObjCt = 0;
#endif

