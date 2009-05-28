// Copyright (c) 2009 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef _V8HANDLER_CTOCPP_H
#define _V8HANDLER_CTOCPP_H

#ifndef BUILDING_CEF_SHARED
#pragma message("Warning: "__FILE__" may be accessed DLL-side only")
#else // BUILDING_CEF_SHARED

#include "cef.h"
#include "cef_capi.h"
#include "ctocpp.h"


// Wrap a C v8handler structure with a C++ v8handler class.
// This class may be instantiated and accessed DLL-side only.
class CefV8HandlerCToCpp
    : public CefCToCpp<CefV8HandlerCToCpp, CefV8Handler, cef_v8handler_t>
{
public:
  CefV8HandlerCToCpp(cef_v8handler_t* str)
    : CefCToCpp<CefV8HandlerCToCpp, CefV8Handler, cef_v8handler_t>(str) {}
  virtual ~CefV8HandlerCToCpp() {}

  // CefV8Handler methods
  virtual bool Execute(const std::wstring& name,
                       CefRefPtr<CefV8Value> object,
                       CefV8ValueList& arguments,
                       CefRefPtr<CefV8Value>& retval,
                       std::wstring& exception);
};


#endif // BUILDING_CEF_SHARED
#endif // _V8HANDLER_CTOCPP_H
