#include "tnt_scene.h"

#include "tnt_math.h"
#include "tnt_render_types.h"

void scene_init(Scene *scene, MemoryArena *arena) {
  scene->arena = arena;
  scene->camera = push_struct_zero(arena, Camera);

  camera_create(scene->camera, 45.0f, 0.5625f, 0.1f, 1000.0f);
}

void scene_update(Scene *scene, OS_Input *input, f32 dt) {
  camera_update(scene->camera, input, dt);
}

Camera *scene_get_camera(Scene *scene) { return scene->camera; }
