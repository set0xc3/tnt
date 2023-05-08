#include "tnt_math.h"
#if !defined(TNT_ENTITY_H)
#define TNT_ENTITY_H

#include "tnt_base_types.h"
#include "tnt_render_types.h"

typedef struct Entity Entity;
struct Entity {
  u64 uuid;
  Transform transform;
  R_Mesh *mesh;
};

void entity_set_mesh(Entity *entity, R_Mesh *mesh);

#endif  // TNT_ENTITY_H
