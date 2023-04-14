#if !defined(TNT_MEMORY_ARENA_H)
#define TNT_MEMORY_ARENA_H

#include "tnt_types.h"

/* Arena

Permanent Allocation
Transient Allocation
Scratch/Temporary Allocation

*/

// API

typedef struct TNT_Arena TNT_Arena;
struct TNT_Arena {
	u8 *data;
  u64 size;
  u64 offset;
};

#define DEFAULT_ARENA_SIZE Gigabytes(4)
#define DEFAULT_ALIGNMENT (8 * sizeof(void *))

TNT_Arena *arena_create(u64 size);
TNT_Arena *arena_create_default(void);
void       arena_release(TNT_Arena *arena);
u8        *arena_push(TNT_Arena *arena, u64 size);
u8        *arena_push_zero(TNT_Arena *arena, u64 size);
void       arena_pop(TNT_Arena *arena, u64 size);
void       arena_clear(TNT_Arena *arena);
u64        arena_get_offset(TNT_Arena *arena);

// Helpers

#define push_array(arena, type, count) arena_push(arena, sizeof(type) * count)
#define push_array_zero(arena, type, count) arena_push_zero(arena, sizeof(type) * count)
#define push_struct(arena, type) (type *)push_array(arena, type, 1)
#define push_struct_zero(arena, type) (type *)push_array_zero(arena, type, 1)
#define pop_array(arena, type, count) arena_pop(arena, sizeof(type) * count)

// ArenaTemp

typedef struct TNT_ArenaTemp TNT_ArenaTemp;
struct TNT_ArenaTemp {
  TNT_Arena *arena;
  u64 offset;
};

TNT_ArenaTemp arena_temp_begin(TNT_Arena *arena);
void 			    arena_temp_end(TNT_ArenaTemp temp);
TNT_ArenaTemp arena_get_scratch(TNT_Arena *arena);

#endif // TNT_MEMORY_ARENA_H
