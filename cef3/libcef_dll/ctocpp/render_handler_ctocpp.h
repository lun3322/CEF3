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

#ifndef CEF_LIBCEF_DLL_CTOCPP_RENDER_HANDLER_CTOCPP_H_
#define CEF_LIBCEF_DLL_CTOCPP_RENDER_HANDLER_CTOCPP_H_
#pragma once

#ifndef BUILDING_CEF_SHARED
#pragma message("Warning: "__FILE__" may be accessed DLL-side only")
#else  // BUILDING_CEF_SHARED

#include "include/cef_render_handler.h"
#include "include/capi/cef_render_handler_capi.h"
#include "libcef_dll/ctocpp/ctocpp.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed DLL-side only.
class CefRenderHandlerCToCpp
    : public CefCToCpp<CefRenderHandlerCToCpp, CefRenderHandler,
        cef_render_handler_t> {
 public:
  explicit CefRenderHandlerCToCpp(cef_render_handler_t* str)
      : CefCToCpp<CefRenderHandlerCToCpp, CefRenderHandler,
          cef_render_handler_t>(str) {}

  // CefRenderHandler methods
  bool GetRootScreenRect(CefRefPtr<CefBrowser> browser, CefRect& rect) override;
  bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) override;
  bool GetScreenPoint(CefRefPtr<CefBrowser> browser, int viewX, int viewY,
      int& screenX, int& screenY) override;
  bool GetScreenInfo(CefRefPtr<CefBrowser> browser,
      CefScreenInfo& screen_info) override;
  void OnPopupShow(CefRefPtr<CefBrowser> browser, bool show) override;
  void OnPopupSize(CefRefPtr<CefBrowser> browser, const CefRect& rect) override;
  void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type,
      const RectList& dirtyRects, const void* buffer, int width,
      int height) override;
  void OnCursorChange(CefRefPtr<CefBrowser> browser, CefCursorHandle cursor,
      CursorType type, const CefCursorInfo& custom_cursor_info) override;
  bool StartDragging(CefRefPtr<CefBrowser> browser,
      CefRefPtr<CefDragData> drag_data, DragOperationsMask allowed_ops, int x,
      int y) override;
  void UpdateDragCursor(CefRefPtr<CefBrowser> browser,
      DragOperation operation) override;
  void OnScrollOffsetChanged(CefRefPtr<CefBrowser> browser) override;
};

#endif  // BUILDING_CEF_SHARED
#endif  // CEF_LIBCEF_DLL_CTOCPP_RENDER_HANDLER_CTOCPP_H_

