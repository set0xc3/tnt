#if !defined(TNT_CAMERA_H)
#define TNT_CAMERA_H

#include "tnt_base_types.h"
#include "tnt_math.h"
#include "tnt_os.h"

typedef struct Camera {
  Vec3 position;
  Vec3 rotation;
  Vec3 scale;
  Vec3 target;

  f32 distance_from_target;
  f32 angle_around_target;
  f32 pitch;
  f32 yaw;
  f32 roll;

  f32 move_speed;
  f32 rotate_speed;

  f32 fov;
  f32 aspect;
  f32 near;
  f32 far;
  Mat4 orthographic_matrix;
  Mat4 perspective_matrix;
  Mat4 view_matrix;
} Camera;

void camera_on_resize(Camera *camera, f32 width, f32 height);

void camera_create(Camera *camera, f32 fov, f32 aspect, f32 near, f32 far);
void camera_destroy(Camera *camera);
void camera_update(Camera *camera, OS_Input *input, f32 dt);

Mat4 camera_get_orthographic_matrix(Camera *camera);
Mat4 camera_get_perspective_matrix(Camera *camera);
Mat4 camera_get_view_matrix(Camera *camera);

#endif  // TNT_CAMERA_H
