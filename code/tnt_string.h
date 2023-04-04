#if !defined(TNT_STRING_H)
#define TNT_STRING_H

#include "tnt_types.h"

typedef struct String8 String8;
struct String8 {
	u8 *data;
	u32 size;
};

#define str8(s) (String8){(u8*)s, sizeof(s)-1}
#define str8_to_char(s) ((char*)s.data)
#define str_len(s) (s.size)

#endif // TNT_STRING_H
