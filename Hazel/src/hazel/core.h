#ifndef _CORE_H_
#define _CORE_H_

#ifdef HAZEL_PLATFORM_WINDOWS

#ifdef HAZEL_BUILD_DLL
#define HAZEL_API __declspec(dllexport)
#else
#define HAZEL_API __declspec(dllimport)
#endif

#else
#error Hazel only support Windows!
#endif

#define BIT(x) (1 << x)

#endif
