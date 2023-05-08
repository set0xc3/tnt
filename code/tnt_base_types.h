#ifndef TNT_BASE_TYPES_H
#define TNT_BASE_TYPES_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define local_variable static
#define global_variable static
#define internal static

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

typedef i8 b8;
typedef i16 b16;
typedef i32 b32;
typedef i64 b64;

typedef void FunctionHandle;

#define Bytes(value) (value)
#define Kilobytes(value) (value << 10)
#define Megabytes(value) (value << 20)
#define Gigabytes(value) ((u64)(value) << 30)
#define Terabytes(value) ((u64)(value) << 40)

#define ArrayCount(a) (sizeof((a)) / sizeof(*(a)))
#define GetMember(st, m) ((u64) & (((st *)0)->m))

#ifdef __GNUC__
#define PLATFORM_LINUX
#elif __WIN32__
#define PLATFORM_WINDOWS
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
#define ASSERT(expr) \
  if (expr) {        \
    ASSERT_BREAK();  \
  }
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

#ifdef PLATFORM_WINDOWS
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)
#else
#define EXPORT __attribute__((visibility("default")))
#define IMPORT
#endif

#endif  // TNT_BASE_TYPES_H
