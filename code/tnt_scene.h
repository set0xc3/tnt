#if !defined(TNT_SCENE_H)
#define TNT_SCENE_H

#include "tnt_base_types.h"
#include "tnt_camera.h"
#include "tnt_entity.h"
#include "tnt_memory_arena.h"
#include "tnt_os.h"

#define ENTITIES_CAPASITY 256

typedef struct GameObject GameObject;
struct GameObject {
  u64 uuid;
  Transform transform;
  R_Sprite sprite;
  R_Model model;
};

typedef struct Scene Scene;
struct Scene {
  MemoryArena *arena;

  Camera *camera;
  Entity *entities;
  u64 entities_count;
};

void scene_init(Scene *scene, MemoryArena *arena);
void scene_update(Scene *scene, OS_Input *input, f32 dt);

Entity *scene_push_entity(Scene *scene, Vec3 pos, Vec3 scale);
Entity *scene_pop_entity(Scene *scene);
void scene_remove_entity(Scene *scene, Entity *entity);
Entity *scene_get_entity(Scene *scene, u32 index);
u32 scene_get_entites_count(Scene *scene);
Camera *scene_get_camera(Scene *scene);

#endif  // TNT_SCENE_H
