// Copyright (c) 2008-2009 The Chromium Embedded Framework Authors.
// Portions copyright (c) 2006-2008 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/compiler_specific.h"

#include "third_party/webkit/webcore/config.h"
MSVC_PUSH_WARNING_LEVEL(0);
#include "MemoryCache.h"
#include "TextEncoding.h"
#include "third_party/WebKit/WebCore/platform/network/HTTPParsers.h"
#include "third_party/WebKit/WebKit/chromium/src/WebFrameImpl.h"
MSVC_POP_WARNING();

#include "browser_webkit_glue.h"

#undef LOG
#include "cef_context.h"

#include "base/logging.h"
#include "base/path_service.h"
#include "base/scoped_ptr.h"
#include "base/string16.h"
#include "base/utf_string_conversions.h"
#include "net/base/mime_util.h"
#include "third_party/WebKit/WebKit/chromium/public/WebFrame.h"
#include "third_party/WebKit/WebKit/chromium/public/WebString.h"
#include "webkit/glue/webkit_glue.h"

// Generated by GRIT
#include "grit/webkit_resources.h"

using WebKit::WebFrameImpl;

namespace webkit_glue {

bool IsMediaPlayerAvailable() {
  return true;
}

void PrecacheUrl(const char16* url, int url_length) {}

void AppendToLog(const char* file, int line, const char* msg) {
  logging::LogMessage(file, line).stream() << msg;
}

bool GetApplicationDirectory(FilePath* path) {
  return PathService::Get(base::DIR_EXE, path);
}

bool GetExeDirectory(FilePath* path) {
  return PathService::Get(base::DIR_EXE, path);
}

bool IsPluginRunningInRendererProcess() {
  return true;
}

bool GetPluginFinderURL(std::string* plugin_finder_url) {
  return false;
}

bool IsDefaultPluginEnabled() {
  return false;
}

bool IsProtocolSupportedForMedia(const GURL& url) {
  if (url.SchemeIsFile() || url.SchemeIs("http") || url.SchemeIs("https"))
    return true;
  return false;
}

std::string GetWebKitLocale() {
  const CefSettings& settings = _Context->settings();
  if (settings.locale)
    return WideToUTF8(settings.locale);
  return "en-US";
}

void InitializeTextEncoding() {
  WebCore::UTF8Encoding();
}

v8::Handle<v8::Context> GetV8Context(WebKit::WebFrame* frame)
{
  WebFrameImpl* webFrameImpl = static_cast<WebFrameImpl*>(frame);
  WebCore::Frame* core_frame = webFrameImpl->frame();
  return WebCore::V8Proxy::context(core_frame);
}

void CloseIdleConnections() {
  // Used in benchmarking,  Ignored for CEF.
}

void SetCacheMode(bool enabled) {
  // Used in benchmarking,  Ignored for CEF.
}

void ClearCache()
{
  // Clear the cache by disabling it and then re-enabling it.
  WebCore::cache()->setDisabled(true);
  WebCore::cache()->setDisabled(false);
}

WebKit::WebString StdStringToWebString(const std::string& str) {
  return WebKit::WebString::fromUTF8(str.data(), str.size());
}

std::string WebStringToStdString(const WebKit::WebString& str) {
  std::string ret;
  if (!str.isNull())
    UTF16ToUTF8(str.data(), str.length(), &ret);
  return ret;
}

WebKit::WebString StdWStringToWebString(const std::wstring& str) {
  return StdStringToWebString(WideToUTF8(str));
}

std::wstring WebStringToStdWString(const WebKit::WebString& str) {
  return UTF8ToWide(WebStringToStdString(str));
}

std::string GetProductVersion() {
  const CefSettings& settings = _Context->settings();
  if (settings.product_version)
    return WideToUTF8(settings.product_version);
  return "Chrome/7.0.517.0";
}

bool IsSingleProcess() {
  return true;
}

#if defined(OS_LINUX)
int MatchFontWithFallback(const std::string& face, bool bold,
                          bool italic, int charset) {
  return -1;
}

bool GetFontTable(int fd, uint32_t table, uint8_t* output,
                  size_t* output_length) {
  return false;
}
#endif

void EnableSpdy(bool enable) {
  // Used in benchmarking,  Ignored for CEF.
}

bool IsContentDispositionAttachment(const std::string& cd_header,
                                    std::string& file_name) {
  WTF::String cd_str(cd_header.c_str(), cd_header.length());
  if (WebCore::contentDispositionType(cd_str) ==
    WebCore::ContentDispositionAttachment) {
    WTF::String name_str =
        WebCore::filenameFromHTTPContentDisposition(cd_str);
    if (!name_str.isEmpty()) {
      WTF::CString cstr(name_str.utf8());
      file_name = std::string(cstr.data(), cstr.length());
    }
    return true;
  }
  return false;
}

}  // namespace webkit_glue
