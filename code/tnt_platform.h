#ifndef TNT_PLATFORM_H
#define TNT_PLATFORM_H

#ifdef __gnu_linux__
#define PLATFORM_LINUX 1
#elif __WIN32__
#define PLATFORM_WINDOWS 1
#else
#error missing platform detection
#endif

#ifdef __WIN32__
#define ASSERT_BREAK() (__debugbreak())
#elif __GNUC__
#define ASSERT_BREAK() (__builtin_trap())
#endif

#define STATIC_ASSERT_BREAK(expr) _Static_assert((expr), "(" #expr ") failed")

#ifdef ENABLE_ASSERT
#define ASSERT(expr) if (expr){ ASSERT_BREAK(); }
#define STATIC_ASSERT(expr) STATIC_ASSERT_BREAK(expr)
#else
#define ASSERT(expr)
#define STATIC_ASSERT(expr)
#endif

#ifdef PLATFORM_LINUX
#define PLATFORM_LIBRARY_EXTENSION ".so"
#elif PLATFORM_WINDOWS
#define PLATFORM_LIBRARY_EXTENSION ".dll"
#else
#error missing platform detection
#endif 

#ifdef __WIN32__
#define DLL_EXPORT __declspec(dllexport)
#define DLL_IMPORT __declspec(dllimport) 
#else
#define DLL_EXPORT __attribute__ ((visibility ("default")))
#define DLL_IMPORT
#endif

#endif //TNT_PLATFORM_H