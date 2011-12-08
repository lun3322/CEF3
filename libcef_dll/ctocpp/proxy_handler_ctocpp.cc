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

#include "libcef_dll/ctocpp/proxy_handler_ctocpp.h"


// VIRTUAL METHODS - Body may be edited by hand.

void CefProxyHandlerCToCpp::GetProxyForUrl(const CefString& url,
    CefProxyInfo& proxy_info)
{
  if (CEF_MEMBER_MISSING(struct_, get_proxy_for_url))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: url; type: string_byref_const
  DCHECK(!url.empty());
  if (url.empty())
    return;

  // Execute
  struct_->get_proxy_for_url(struct_,
      url.GetStruct(),
      &proxy_info);
}



#ifndef NDEBUG
template<> long CefCToCpp<CefProxyHandlerCToCpp, CefProxyHandler,
    cef_proxy_handler_t>::DebugObjCt = 0;
#endif

