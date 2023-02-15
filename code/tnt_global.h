#ifndef TNT_GLOBAL_H
#define TNT_GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

#define local_variable  static
#define global_variable static
#define internal        static

typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float    f32;
typedef double   f64;

typedef s8       b8;
typedef s32      b32;

#define KB(value) (value     * 1024)
#define MB(value) (KB(value) * 1024)
#define GB(value) (MB(value) * 1024)
#define TB(value) (GB(value) * 1024)

#define ARRAY_COUNT(a) (sizeof(a) / sizeof(*a))

#endif //TNT_GLOBAL_H