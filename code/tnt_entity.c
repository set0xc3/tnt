#include "tnt_entity.h"

#define ENTITIES_CAPASITY 256

global_variable Entity entities[ENTITIES_CAPASITY];
global_variable u32	entities_count;

Entity *entity_push(Vec3 pos, Vec3 size)
{
	ASSERT(entities_count + 1 > ENTITIES_CAPASITY);

	Entity *ent = entities + entities_count;
	ent->pos = pos;
	ent->size = size;
	entities_count += 1;
	return ent;
}

void entity_pop()
{
  ASSERT(entities_count == 0 || entities_count > ENTITIES_CAPASITY);

	Entity *ent = entities + entities_count-1;
	entity_remove(ent);
}

void entity_remove(Entity *entity)
{
  ASSERT(entities_count == 0 || entities_count > ENTITIES_CAPASITY);

	memset(entity, 0, sizeof(Entity));
	entities_count -= 1;
}

Entity *entity_get(u32 index)
{
  ASSERT(entities_count == 0 || entities_count+index > ENTITIES_CAPASITY);

	Entity *ent = entities + index;
	return ent;
}

void entity_set_mesh(Entity *entity, R_Mesh *mesh)
{
	entity->mesh = mesh;
}

