#if !defined(TNT_MEMORY_ARENA_H)
#define TNT_MEMORY_ARENA_H

#include "tnt_types.h"

/* MemoryArena

Permanent Allocation
Transient Allocation
Scratch/Temporary Allocation

*/

// API

typedef struct TNT_MemoryArena TNT_MemoryArena;
struct TNT_MemoryArena {
	u8 *data;
  u64 size;
  u64 offset;
};

#define DEFAULT_ARENA_SIZE Gigabytes(4)
#define DEFAULT_ALIGNMENT (8 * sizeof(void *))

TNT_MemoryArena *arena_create(u64 size);
TNT_MemoryArena *arena_create_default(void);
void       			 arena_release(TNT_MemoryArena *arena);
u8        			*arena_push(TNT_MemoryArena *arena, u64 size);
u8        			*arena_push_zero(TNT_MemoryArena *arena, u64 size);
void       			 arena_pop(TNT_MemoryArena *arena, u64 size);
void       			 arena_clear(TNT_MemoryArena *arena);
u64        			 arena_get_offset(TNT_MemoryArena *arena);

// Helpers

#define push_array(arena, type, count) arena_push(arena, sizeof(type) * count)
#define push_array_zero(arena, type, count) arena_push_zero(arena, sizeof(type) * count)
#define push_struct(arena, type) (type *)push_array(arena, type, 1)
#define push_struct_zero(arena, type) (type *)push_array_zero(arena, type, 1)
#define pop_array(arena, type, count) arena_pop(arena, sizeof(type) * count)

// MemoryArenaTemp

typedef struct TNT_MemoryArenaTemp TNT_MemoryArenaTemp;
struct TNT_MemoryArenaTemp {
  TNT_MemoryArena *arena;
  u64 offset;
};

TNT_MemoryArenaTemp arena_temp_begin(TNT_MemoryArena *arena);
void 			    			arena_temp_end(TNT_MemoryArenaTemp temp);
TNT_MemoryArenaTemp arena_get_scratch(TNT_MemoryArena *arena);

#endif // TNT_MEMORY_ARENA_H
