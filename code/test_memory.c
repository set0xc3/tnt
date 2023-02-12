typedef struct MemoryArena MemoryArena;
struct MemoryArena 
{
	size_t size;
	u8 *base;
	size_t used;
	u32 _saved_count;
	size_t _saved[8];
};

internal void *_PushSize(MemoryArena *arena, size_t size)
{
	ASSERT((arena->used + size) <= arena->size);
	u8 *result = arena->base + arena->used;
	arena->used += size;
	return (void *)result;
}

internal void ZeroSize(void *ptr, size_t size)
{
	u8 *byte = (u8 *)ptr;
	while (size--) 
	{
		*byte++ = 0;
	}
}

#define PushSize(arena, size) _PushSize((arena), (size))
#define PushArray(arena, count, type) (type *)PushSize(arena, (count) * sizeof(type))
#define PushStruct(arena, type) (type *)PushSize((arena), sizeof(type))
#define ZeroStruct(instance) ZeroSize(&(instance), sizeof(instance))

typedef struct Memory Memory;
struct Memory
{
	size_t permanentStorageSize;
	void *permanentStorage; // required to be cleared to zero
	
	size_t transientStorageSize;
	void *transientStorage;
};

typedef struct Entity Entity;
struct Entity
{
	u32 id;
};

void test_memory(void)
{
	Entity entity = {};
	entity.id = 1;
	
	Memory memory = {};
	memory.permanentStorageSize = MB(64);
	memory.transientStorageSize = MB(200);
	
	memory.permanentStorage = os_memory_reserve(0, (size_t)(memory.permanentStorageSize + memory.transientStorageSize));
	memory.transientStorage = (u8 *)memory.permanentStorage + memory.permanentStorageSize;
	
	MemoryArena *arena = malloc(sizeof(MemoryArena));
	arena->size = memory.permanentStorageSize - sizeof(Entity);
	arena->base = (u8 *)memory.permanentStorage + sizeof(Entity);
	
	{
		Entity *entity = malloc(sizeof(Entity));
		entity->id = 1;
		//PushArray(arena, 1, Entity);
	}
	
	{
		Entity *entity = malloc(sizeof(Entity));
		entity->id = 1;
		//PushStruct(arena, Entity);
	}
	
}