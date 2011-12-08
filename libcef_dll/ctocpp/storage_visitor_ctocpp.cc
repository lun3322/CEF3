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

#include "libcef_dll/ctocpp/storage_visitor_ctocpp.h"


// VIRTUAL METHODS - Body may be edited by hand.

bool CefStorageVisitorCToCpp::Visit(CefStorageType type,
    const CefString& origin, const CefString& key, const CefString& value,
    int count, int total, bool& deleteData)
{
  if (CEF_MEMBER_MISSING(struct_, visit))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: origin; type: string_byref_const
  DCHECK(!origin.empty());
  if (origin.empty())
    return false;
  // Verify param: key; type: string_byref_const
  DCHECK(!key.empty());
  if (key.empty())
    return false;
  // Verify param: value; type: string_byref_const
  DCHECK(!value.empty());
  if (value.empty())
    return false;

  // Translate param: deleteData; type: bool_byref
  int deleteDataInt = deleteData;

  // Execute
  int _retval = struct_->visit(struct_,
      type,
      origin.GetStruct(),
      key.GetStruct(),
      value.GetStruct(),
      count,
      total,
      &deleteDataInt);

  // Restore param:deleteData; type: bool_byref
  deleteData = deleteDataInt?true:false;

  // Return type: bool
  return _retval?true:false;
}



#ifndef NDEBUG
template<> long CefCToCpp<CefStorageVisitorCToCpp, CefStorageVisitor,
    cef_storage_visitor_t>::DebugObjCt = 0;
#endif

