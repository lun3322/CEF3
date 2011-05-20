// Copyright (c) 2011 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool and should not edited
// by hand. See the translator.README.txt file in the tools directory for
// more information.
//
#ifndef _STREAMWRITER_CPPTOC_H
#define _STREAMWRITER_CPPTOC_H

#ifndef BUILDING_CEF_SHARED
#pragma message("Warning: "__FILE__" may be accessed DLL-side only")
#else // BUILDING_CEF_SHARED

#include "include/cef.h"
#include "include/cef_capi.h"
#include "libcef_dll/cpptoc/cpptoc.h"

// Wrap a C++ class with a C structure.
// This class may be instantiated and accessed DLL-side only.
class CefStreamWriterCppToC
    : public CefCppToC<CefStreamWriterCppToC, CefStreamWriter,
        cef_stream_writer_t>
{
public:
  CefStreamWriterCppToC(CefStreamWriter* cls);
  virtual ~CefStreamWriterCppToC() {}
};

#endif // BUILDING_CEF_SHARED
#endif // _STREAMWRITER_CPPTOC_H

