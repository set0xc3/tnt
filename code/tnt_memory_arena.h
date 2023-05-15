#if !defined(TNT_MEMORY_ARENA_H)
#define TNT_MEMORY_ARENA_H

#include "tnt_base_types.h"

/* MemoryArena

Permanent Allocation
Transient Allocation
Scratch/Temporary Allocation

*/

// API

typedef struct MemoryArena {
  u8 *data;
  u64 size;
  u64 offset;
} MemoryArena;

#define DEFAULT_ARENA_SIZE Gigabytes(4)
#define DEFAULT_ALIGNMENT (8 * sizeof(void *))

MemoryArena *arena_create(u64 size);
MemoryArena *arena_create_default(void);
void arena_release(MemoryArena *arena);
u8 *arena_push(MemoryArena *arena, u64 size);
u8 *arena_push_zero(MemoryArena *arena, u64 size);
u8 *arena_pop(MemoryArena *arena, u64 size);
void arena_clear(MemoryArena *arena);
u64 arena_get_offset(MemoryArena *arena);

// Helpers

#define push_array(arena, type, count) \
  (type *)arena_push(arena, sizeof(type) * count)
#define push_array_zero(arena, type, count) \
  (type *)arena_push_zero(arena, sizeof(type) * count)
#define push_struct(arena, type) (type *)push_array(arena, type, 1)
#define push_struct_zero(arena, type) (type *)push_array_zero(arena, type, 1)
#define pop_array(arena, type, count) \
  (type *)arena_pop(arena, sizeof(type) * count)

// MemoryArenaTemp

typedef struct MemoryArenaTemp {
  MemoryArena *arena;
  u64 offset;
} MemoryArenaTemp;

MemoryArenaTemp arena_temp_begin(MemoryArena *arena);
void arena_temp_end(MemoryArenaTemp temp);
MemoryArenaTemp arena_get_scratch(MemoryArena *arena);

#endif  // TNT_MEMORY_ARENA_H
