#include "tnt_memory_arena.h"
#include "tnt_logger.h"
#include "tnt_os.h"

#define BASE_ADDRESS Terabytes(1)

TNT_MemoryArena *arena_create(u64 size) {
  TNT_MemoryArena *arena = os_memory_alloc((void*)BASE_ADDRESS, sizeof(TNT_MemoryArena));
	arena->data   = os_memory_alloc((void*)BASE_ADDRESS, size);
	arena->size   = size;
	arena->offset = 0;
  return arena;
}

TNT_MemoryArena *arena_create_default(void) { 
	return arena_create(DEFAULT_ARENA_SIZE); 
}

void arena_release(TNT_MemoryArena *arena) { 
	ASSERT(!arena);

	free(arena->data); 
	free(arena); 
}

u8 *arena_push(TNT_MemoryArena *arena, u64 size) {
  if (arena->offset + size > arena->size) {
    LOG_FATAL("Handle out-of-memory");
		ASSERT(true);
  }
  u8 *pos = (u8 *)arena->data + arena->offset;
  arena->offset += size;
  return pos;
}

u8 *arena_push_zero(TNT_MemoryArena *arena, u64 size) {
  void *memory = arena_push(arena, size);
  if (memory == 0) {
    return 0;
  }
  memset(memory, 0, size);
  return memory;
}


u8 *arena_pop(TNT_MemoryArena *arena, u64 size) {
  if (arena->offset - size < 0) {
    LOG_FATAL("Handle out-of-memory");
		ASSERT(true);
  }
  arena->offset -= size;
  u8 *pos = (u8 *)arena->offset - size;
	return pos;
}

void arena_clear(TNT_MemoryArena *arena) { 
	arena->offset = 0; 
}

u64 arena_get_offset(TNT_MemoryArena *arena) { 
	return arena->offset; 
}

// ArenaTemp

TNT_MemoryArenaTemp arena_temp_begin(TNT_MemoryArena *arena) {
  TNT_MemoryArenaTemp result = {0};
  result.arena = arena;
  result.offset = arena->offset;
  return result;
}

void arena_temp_end(TNT_MemoryArenaTemp temp) { 
	temp.arena->offset = temp.offset; 
}

TNT_MemoryArenaTemp arena_get_scratch(TNT_MemoryArena *arena) {
  TNT_MemoryArenaTemp temp = {0};
  temp.arena = arena;
  temp.offset = arena->offset;
  return temp;
}
