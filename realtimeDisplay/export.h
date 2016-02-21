#ifndef _UDPSocket_EXPORT_H_
#define _UDPSocket_EXPORT_H_


#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
#   ifdef UDPSocket_LIBRARY
#      define UDPSocket_EXPORT __declspec(dllexport)
#   else
#      define UDPSocket_EXPORT __declspec(dllimport)
#   endif
#else
#   ifdef UDPSocket_LIBRARY
#      define UDPSocket_EXPORT __attribute__ ((visibility("default")))
#   else
#      define UDPSocket_EXPORT
#   endif
#endif

#endif
