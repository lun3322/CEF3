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

#ifndef CEF_LIBCEF_DLL_CPPTOC_ALLOW_CERTIFICATE_ERROR_CALLBACK_CPPTOC_H_
#define CEF_LIBCEF_DLL_CPPTOC_ALLOW_CERTIFICATE_ERROR_CALLBACK_CPPTOC_H_
#pragma once

#ifndef BUILDING_CEF_SHARED
#pragma message("Warning: "__FILE__" may be accessed DLL-side only")
#else  // BUILDING_CEF_SHARED

#include "include/cef_request_handler.h"
#include "include/capi/cef_request_handler_capi.h"
#include "libcef_dll/cpptoc/cpptoc.h"

// Wrap a C++ class with a C structure.
// This class may be instantiated and accessed DLL-side only.
class CefAllowCertificateErrorCallbackCppToC
    : public CefCppToC<CefAllowCertificateErrorCallbackCppToC,
        CefAllowCertificateErrorCallback,
        cef_allow_certificate_error_callback_t> {
 public:
  explicit CefAllowCertificateErrorCallbackCppToC(
      CefAllowCertificateErrorCallback* cls);
  virtual ~CefAllowCertificateErrorCallbackCppToC() {}
};

#endif  // BUILDING_CEF_SHARED
#endif  // CEF_LIBCEF_DLL_CPPTOC_ALLOW_CERTIFICATE_ERROR_CALLBACK_CPPTOC_H_

