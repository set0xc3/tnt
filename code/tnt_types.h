#ifndef TNT_TYPES_H
#define TNT_TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

#define local_variable  static
#define global_variable static
#define internal        static

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float  f32;
typedef double f64;

typedef i8  b8;
typedef i16 b16;
typedef i32 b32;
typedef i64 b64;

typedef uintptr_t uintptr;

#define Bytes(value)     (value)
#define Kilobytes(value) (value << 10)
#define Megabytes(value) (value << 20)
#define Gigabytes(value) ((u64)(value) << 30)
#define Terabytes(value) ((u64)(value) << 40)

#define ArrayCount(a) (sizeof(a) / sizeof(*a))

#endif //TNT_TYPES_H
