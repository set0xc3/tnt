#include "tnt_math.h"
#if !defined(TNT_ENTITY_H)
#define TNT_ENTITY_H

#include "tnt_types.h"
#include "tnt_render_types.h"

typedef struct Entity Entity;
struct Entity 
{
	u64 uuid;
	Vec3 position;
	Vec3 rotation;
	Vec3 size;
	R_Mesh *mesh;
};

void entity_set_mesh(Entity *entity, R_Mesh *mesh);

#endif // TNT_ENTITY_H
