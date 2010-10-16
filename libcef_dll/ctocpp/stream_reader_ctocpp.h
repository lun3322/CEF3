// Copyright (c) 2010 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// -------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool and should not edited
// by hand. See the translator.README.txt file in the tools directory for
// more information.
//

#ifndef _STREAMREADER_CTOCPP_H
#define _STREAMREADER_CTOCPP_H

#ifndef USING_CEF_SHARED
#pragma message("Warning: "__FILE__" may be accessed wrapper-side only")
#else // USING_CEF_SHARED

#include "include/cef.h"
#include "include/cef_capi.h"
#include "libcef_dll/ctocpp/ctocpp.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed wrapper-side only.
class CefStreamReaderCToCpp
    : public CefCToCpp<CefStreamReaderCToCpp, CefStreamReader,
        cef_stream_reader_t>
{
public:
  CefStreamReaderCToCpp(cef_stream_reader_t* str)
      : CefCToCpp<CefStreamReaderCToCpp, CefStreamReader, cef_stream_reader_t>(
          str) {}
  virtual ~CefStreamReaderCToCpp() {}

  // CefStreamReader methods
  virtual size_t Read(void* ptr, size_t size, size_t n);
  virtual int Seek(long offset, int whence);
  virtual long Tell();
  virtual int Eof();
};

#endif // USING_CEF_SHARED
#endif // _STREAMREADER_CTOCPP_H

