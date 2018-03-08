#pragma once

#include <locale>
#include <codecvt>
#include <string>
#include <sstream>

namespace dxvk::str {
  
  inline void format1(std::stringstream&) { }
  
  template<typename T, typename... Tx>
  void format1(std::stringstream& str, const T& arg, const Tx&... args) {
    str << arg;
    format1(str, args...);
  }
  
  template<typename... Args>
  std::string format(const Args&... args) {
    std::stringstream stream;
    format1(stream, args...);
    return stream.str();
  }
#ifdef WINEBUILD
  // FIXME: dirty hack to fix wstring/string manipulation problem

  //  inline std::string fromws(const std::wstring& ws) {
  //      std::string a1(wine_dbgstr_w(ws.c_str()));
  //    // skip first 2 and last 1 characters from L"string"
  //    return a1.substr(2, a1.size() - 3);
  //  }

  inline std::string fromws( const std::wstring& ws ) {
    const wchar_t * str = ws.c_str();
    char *dst, *res;
    size_t size;
    int n;

    const wchar_t *end = str;
    while (*end) end++;
    n = end - str;

    char buffer_tmp[256];

    if (n < 0) n = 0;
    size = 12 + std::min(300, n * 5);
    dst = res = buffer_tmp;

    while (n-- > 0 && dst <= res + size - 10) {
      wchar_t c = *str++;
      switch (c) {
      case '\n': *dst++ = '\\'; *dst++ = 'n'; break;
      case '\r': *dst++ = '\\'; *dst++ = 'r'; break;
      case '\t': *dst++ = '\\'; *dst++ = 't'; break;
      case '"':  *dst++ = '\\'; *dst++ = '"'; break;
      case '\\': *dst++ = '\\'; *dst++ = '\\'; break;
      default:
        if (c >= ' ' && c <= 126)
          *dst++ = c;
        else {
          *dst++ = '\\';
          sprintf(dst,"%04x",c);
          dst+=4;
        }
      }
    }

    if (n > 0) {
      *dst++ = '.';
      *dst++ = '.';
      *dst++ = '.';
    }
    *dst++ = 0;

    return std::string(res);
}
#else
  inline std::string fromws(const std::wstring& ws) {
    return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(ws);
  }
#endif
}
