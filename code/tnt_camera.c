#include "tnt_camera.h"

#include "tnt_math.h"

void camera_on_resize(Camera *camera, f32 width, f32 height) {
  f32 aspect = width / height;
  f32 half_height = height / 2.0f;
  f32 half_width = half_height * aspect;

  camera->aspect = aspect;
  camera->orthographic_matrix =
      m_orthographic_rh_zo(-half_width, half_width, -half_height, half_height,
                           camera->near, camera->far);
  camera->perspective_matrix = m_perspective_rh_zo(camera->fov, camera->aspect,
                                                   camera->near, camera->far);
}

void camera_create(Camera *camera, f32 fov, f32 aspect, f32 near, f32 far) {
  camera->position = v3(0.0f, 0.0f, 3.0f);
  camera->rotation = v3(0.0f, 0.0f, 0.0f);
  camera->scale = v3(1.0f, 1.0f, 1.0f);

  camera->move_speed = 8.0f;
  camera->rotate_speed = 1.0f;

  camera->fov = fov;
  camera->near = near;
  camera->far = far;
  camera->perspective_matrix = m_perspective_rh_no(fov, aspect, near, far);
}

void camera_destroy(Camera *camera) { memset(camera, 0, sizeof(Camera)); }

void camera_update(Camera *camera, OS_Input *input, f32 dt) {
  Vec3 camera_front = v3(0.0f, 0.0f, -1.0f);
  Vec3 camera_up = v3(0.0f, 1.0f, 0.0f);

  if (os_input_key_pressed(input, OS_KEYCODE_W)) {
    camera->position.x += camera->move_speed * camera_front.x * dt;
    camera->position.y += camera->move_speed * camera_front.y * dt;
    camera->position.z += camera->move_speed * camera_front.z * dt;
  }
  if (os_input_key_pressed(input, OS_KEYCODE_S)) {
    camera->position.x -= camera->move_speed * camera_front.x * dt;
    camera->position.y -= camera->move_speed * camera_front.y * dt;
    camera->position.z -= camera->move_speed * camera_front.z * dt;
  }
  if (os_input_key_pressed(input, OS_KEYCODE_A)) {
    camera->position.x -=
        norm_v3(cross(camera_front, camera_up)).x * camera->move_speed * dt;
    camera->position.y -=
        norm_v3(cross(camera_front, camera_up)).y * camera->move_speed * dt;
    camera->position.z -=
        norm_v3(cross(camera_front, camera_up)).z * camera->move_speed * dt;
  }
  if (os_input_key_pressed(input, OS_KEYCODE_D)) {
    camera->position.x +=
        norm_v3(cross(camera_front, camera_up)).x * camera->move_speed * dt;
    camera->position.y +=
        norm_v3(cross(camera_front, camera_up)).y * camera->move_speed * dt;
    camera->position.z +=
        norm_v3(cross(camera_front, camera_up)).z * camera->move_speed * dt;
  }
  if (os_input_key_pressed(input, OS_KEYCODE_Q)) {
    camera->fov += 100.0f * dt;
  }
  if (os_input_key_pressed(input, OS_KEYCODE_E)) {
    camera->fov -= 100.0f * dt;
  }

  camera->perspective_matrix = m_perspective_rh_no(
      m_to_radiansf(camera->fov), camera->aspect, camera->near, camera->far);
  camera->view_matrix = m_look_at_rh(
      camera->position, add_v3(camera->position, camera_front), camera_up);
}

Mat4 camera_get_orthographic_matrix(Camera *camera) {
  return camera->orthographic_matrix;
}

Mat4 camera_get_perspective_matrix(Camera *camera) {
  return camera->perspective_matrix;
}

Mat4 camera_get_view_matrix(Camera *camera) { return camera->view_matrix; }
