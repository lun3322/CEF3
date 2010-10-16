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

#ifndef _POSTDATA_CTOCPP_H
#define _POSTDATA_CTOCPP_H

#ifndef USING_CEF_SHARED
#pragma message("Warning: "__FILE__" may be accessed wrapper-side only")
#else // USING_CEF_SHARED

#include "include/cef.h"
#include "include/cef_capi.h"
#include "libcef_dll/ctocpp/ctocpp.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed wrapper-side only.
class CefPostDataCToCpp
    : public CefCToCpp<CefPostDataCToCpp, CefPostData, cef_post_data_t>
{
public:
  CefPostDataCToCpp(cef_post_data_t* str)
      : CefCToCpp<CefPostDataCToCpp, CefPostData, cef_post_data_t>(str) {}
  virtual ~CefPostDataCToCpp() {}

  // CefPostData methods
  virtual size_t GetElementCount();
  virtual void GetElements(ElementVector& elements);
  virtual bool RemoveElement(CefRefPtr<CefPostDataElement> element);
  virtual bool AddElement(CefRefPtr<CefPostDataElement> element);
  virtual void RemoveElements();
};

#endif // USING_CEF_SHARED
#endif // _POSTDATA_CTOCPP_H

