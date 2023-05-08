#include "tnt_memory_arena.h"

#include "tnt_logger.h"
#include "tnt_os.h"

MemoryArena *arena_create(u64 size) {
  MemoryArena *arena = os_memory_alloc(0, sizeof(MemoryArena));
  arena->data = os_memory_alloc(0, size);
  arena->size = size;
  arena->offset = 0;
  return arena;
}

MemoryArena *arena_create_default(void) {
  return arena_create(DEFAULT_ARENA_SIZE);
}

void arena_release(MemoryArena *arena) {
  ASSERT(!arena);

  free(arena->data);
  free(arena);
}

u8 *arena_push(MemoryArena *arena, u64 size) {
  if (arena->offset + size > arena->size) {
    LOG_FATAL("Handle out-of-memory");
    ASSERT(true);
  }
  u8 *pos = (u8 *)arena->data + arena->offset;
  arena->offset += size;
  return pos;
}

u8 *arena_push_zero(MemoryArena *arena, u64 size) {
  void *memory = arena_push(arena, size);
  if (memory == 0) {
    return 0;
  }
  memset(memory, 0, size);
  return memory;
}

u8 *arena_pop(MemoryArena *arena, u64 size) {
  if (arena->offset == 0) {
    LOG_FATAL("Handle out-of-memory");
    ASSERT(true);
  }
  arena->offset -= size;
  u8 *pos = (u8 *)arena->offset - size;
  return pos;
}

void arena_clear(MemoryArena *arena) { arena->offset = 0; }

u64 arena_get_offset(MemoryArena *arena) { return arena->offset; }

// ArenaTemp

MemoryArenaTemp arena_temp_begin(MemoryArena *arena) {
  MemoryArenaTemp result = {0};
  result.arena = arena;
  result.offset = arena->offset;
  return result;
}

void arena_temp_end(MemoryArenaTemp temp) { temp.arena->offset = temp.offset; }

MemoryArenaTemp arena_get_scratch(MemoryArena *arena) {
  MemoryArenaTemp temp = {0};
  temp.arena = arena;
  temp.offset = arena->offset;
  return temp;
}
