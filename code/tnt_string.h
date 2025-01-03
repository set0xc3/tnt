#if !defined(TNT_STRING_H)
#define TNT_STRING_H

#include "tnt_base_types.h"

typedef struct String8 {
  u8 *data;
  u32 size;
} String8;

#define str8(s) \
  (String8) { (u8 *)s, sizeof(s) - 1 }
#define str8_to_char(s) ((char *)s.data)
#define str_len(s) (s.size)

#endif  // TNT_STRING_H
