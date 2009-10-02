// Copyright (c) 2009 The Chromium Embedded Framework Authors. All rights
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

#include "libcef_dll/cpptoc/post_data_cpptoc.h"
#include "libcef_dll/cpptoc/post_data_element_cpptoc.h"


// GLOBAL FUNCTIONS - Body may be edited by hand.

CEF_EXPORT cef_post_data_t* cef_post_data_create()
{
  CefRefPtr<CefPostData> impl = CefPostData::CreatePostData();
  if(impl.get())
    return CefPostDataCppToC::Wrap(impl);
  return NULL;
}


// MEMBER FUNCTIONS - Body may be edited by hand.

size_t CEF_CALLBACK post_data_get_element_count(struct _cef_post_data_t* self)
{
  DCHECK(self);
  if(!self)
    return 0;

  return CefPostDataCppToC::Get(self)->GetElementCount();
}

struct _cef_post_data_element_t* CEF_CALLBACK post_data_get_elements(
    struct _cef_post_data_t* self, int elementIndex)
{
  DCHECK(self);
  if(!self)
    return NULL;

  CefPostData::ElementVector elements;
  CefPostDataCppToC::Get(self)->GetElements(elements);

  if(elementIndex < 0 || elementIndex >= (int)elements.size())
    return NULL;

  return CefPostDataElementCppToC::Wrap(elements[elementIndex]);
}

int CEF_CALLBACK post_data_remove_element(struct _cef_post_data_t* self,
    struct _cef_post_data_element_t* element)
{
  DCHECK(self);
  DCHECK(element);
  if(!self || !element)
    return 0;

  CefRefPtr<CefPostDataElement> selfElementPtr =
      CefPostDataElementCppToC::Unwrap(element);
  return CefPostDataCppToC::Get(self)->RemoveElement(selfElementPtr);
}

int CEF_CALLBACK post_data_add_element(struct _cef_post_data_t* self,
    struct _cef_post_data_element_t* element)
{
  DCHECK(self);
  DCHECK(element);
  if(!self || !element)
    return 0;

  CefRefPtr<CefPostDataElement> selfElementPtr =
      CefPostDataElementCppToC::Unwrap(element);
  return CefPostDataCppToC::Get(self)->AddElement(selfElementPtr);
}

void CEF_CALLBACK post_data_remove_elements(struct _cef_post_data_t* self)
{
  DCHECK(self);
  if(!self)
    return;

  CefPostDataCppToC::Get(self)->RemoveElements();
}


// CONSTRUCTOR - Do not edit by hand.

CefPostDataCppToC::CefPostDataCppToC(CefPostData* cls)
    : CefCppToC<CefPostDataCppToC, CefPostData, cef_post_data_t>(cls)
{
  struct_.struct_.get_element_count = post_data_get_element_count;
  struct_.struct_.get_elements = post_data_get_elements;
  struct_.struct_.remove_element = post_data_remove_element;
  struct_.struct_.add_element = post_data_add_element;
  struct_.struct_.remove_elements = post_data_remove_elements;
}

#ifdef _DEBUG
long CefCppToC<CefPostDataCppToC, CefPostData, cef_post_data_t>::DebugObjCt = 0;
#endif

