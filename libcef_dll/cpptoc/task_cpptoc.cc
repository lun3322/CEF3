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

#include "libcef_dll/cpptoc/task_cpptoc.h"


// MEMBER FUNCTIONS - Body may be edited by hand.

void CEF_CALLBACK task_execute(struct _cef_task_t* self,
    cef_thread_id_t threadId)
{
  DCHECK(self);
  if(!self)
    return;

  CefTaskCppToC::Get(self)->Execute(threadId);
}


// CONSTRUCTOR - Do not edit by hand.

CefTaskCppToC::CefTaskCppToC(CefTask* cls)
    : CefCppToC<CefTaskCppToC, CefTask, cef_task_t>(cls)
{
  struct_.struct_.execute = task_execute;
}

#ifdef _DEBUG
long CefCppToC<CefTaskCppToC, CefTask, cef_task_t>::DebugObjCt = 0;
#endif

