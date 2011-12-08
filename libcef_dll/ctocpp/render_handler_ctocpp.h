// Copyright (c) 2011 The Chromium Embedded Framework Authors. All rights
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

#ifndef _RENDERHANDLER_CTOCPP_H
#define _RENDERHANDLER_CTOCPP_H

#ifndef BUILDING_CEF_SHARED
#pragma message("Warning: "__FILE__" may be accessed DLL-side only")
#else // BUILDING_CEF_SHARED

#include "include/cef.h"
#include "include/cef_capi.h"
#include "libcef_dll/ctocpp/ctocpp.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed DLL-side only.
class CefRenderHandlerCToCpp
    : public CefCToCpp<CefRenderHandlerCToCpp, CefRenderHandler,
        cef_render_handler_t>
{
public:
  CefRenderHandlerCToCpp(cef_render_handler_t* str)
      : CefCToCpp<CefRenderHandlerCToCpp, CefRenderHandler,
          cef_render_handler_t>(str) {}
  virtual ~CefRenderHandlerCToCpp() {}

  // CefRenderHandler methods
  virtual bool GetViewRect(CefRefPtr<CefBrowser> browser,
      CefRect& rect) OVERRIDE;
  virtual bool GetScreenRect(CefRefPtr<CefBrowser> browser,
      CefRect& rect) OVERRIDE;
  virtual bool GetScreenPoint(CefRefPtr<CefBrowser> browser, int viewX,
      int viewY, int& screenX, int& screenY) OVERRIDE;
  virtual void OnPopupShow(CefRefPtr<CefBrowser> browser, bool show) OVERRIDE;
  virtual void OnPopupSize(CefRefPtr<CefBrowser> browser,
      const CefRect& rect) OVERRIDE;
  virtual void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type,
      const RectList& dirtyRects, const void* buffer) OVERRIDE;
  virtual void OnCursorChange(CefRefPtr<CefBrowser> browser,
      CefCursorHandle cursor) OVERRIDE;
};

#endif // BUILDING_CEF_SHARED
#endif // _RENDERHANDLER_CTOCPP_H

