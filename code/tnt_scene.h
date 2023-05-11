#if !defined(TNT_SCENE_H)
#define TNT_SCENE_H

#include "tnt_base_types.h"
#include "tnt_camera.h"
#include "tnt_memory_arena.h"
#include "tnt_os.h"
#include "tnt_render_types.h"

#define ENTITIES_CAPASITY 256

typedef struct Transform {
  Vec3 position;
  Vec3 rotation;
  Vec3 scale;
} Transform;

typedef struct GameObject {
  u64 uuid;
  Transform transform;
  R_Sprite sprite;
  R_Model model;
} GameObject;

typedef struct Scene {
  MemoryArena *arena;

  Camera *camera;
} Scene;

Mat4 transform_get_model(GameObject *object);

void scene_init(Scene *scene, MemoryArena *arena);
void scene_update(Scene *scene, OS_Input *input, f32 dt);

#endif  // TNT_SCENE_H
