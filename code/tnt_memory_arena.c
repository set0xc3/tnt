#include "tnt_memory_arena.h"
#include "tnt_logger.h"
#include "tnt_types_platform.h"
#include "tnt_os.h"

#define BASE_ADDRESS Terabytes(1)

TNT_Arena *arena_create(u64 size) {
  TNT_Arena *arena = os_memory_alloc((void*)BASE_ADDRESS, sizeof(TNT_Arena));
	arena->data = os_memory_alloc((void*)BASE_ADDRESS, size);
	arena->size = size;
	arena->offset = 0;
  return arena;
}

TNT_Arena *arena_create_default(void) { 
	return arena_create(DEFAULT_ARENA_SIZE); 
}

void arena_release(TNT_Arena *arena) { 
	free(arena->data); 
	free(arena); 
}

u8 *arena_push(TNT_Arena *arena, u64 size) {
  if (arena->offset + size > arena->size) {
    LOG_FATAL("Handle out-of-memory");
		ASSERT(true);
  }
  u8 *pos = (u8 *)arena->data + arena->offset;
  arena->offset += size;
  return pos;
}

u8 *arena_push_zero(TNT_Arena *arena, u64 size) {
  void *memory = arena_push(arena, size);
  if (memory == 0) {
    return 0;
  }
  memset(memory, 0, size);
  return memory;
}


void arena_pop(TNT_Arena *arena, u64 size) {
  if (arena->offset - size < 0) {
    LOG_FATAL("Handle out-of-memory");
		ASSERT(true);
  }
  u8 *pos = (u8 *)arena->offset - size;
  arena->offset -= size;
}

void arena_clear(TNT_Arena *arena) { 
	arena->offset = 0; 
}

u64 arena_get_offset(TNT_Arena *arena) { 
	return arena->offset; 
}

// ArenaTemp

TNT_ArenaTemp arena_temp_begin(TNT_Arena *arena) {
  TNT_ArenaTemp result = {0};
  result.arena = arena;
  result.offset = arena->offset;
  return result;
}

void arena_temp_end(TNT_ArenaTemp temp) { 
	temp.arena->offset = temp.offset; 
}

TNT_ArenaTemp arena_get_scratch(TNT_Arena *arena) {
  TNT_ArenaTemp temp = {0};
  temp.arena = arena;
  temp.offset = arena->offset;
  return temp;
}
