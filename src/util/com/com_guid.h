#pragma once

#include <ostream>

#include "com_include.h"

#ifdef WINEBUILD
#define DXVK_DEFINE_GUID(iface) \
  template<> inline GUID const& __wine_uuidof<iface> () { return iface::guid; }
#else
#define DXVK_DEFINE_GUID(iface) \
  template<> inline GUID const& __mingw_uuidof<iface> () { return iface::guid; }
#endif

std::ostream& operator << (std::ostream& os, REFIID guid);
