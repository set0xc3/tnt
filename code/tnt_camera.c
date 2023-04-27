#include "tnt_camera.h"

void camera_create(Camera *camera, f32 fov, f32 aspect, f32 near, f32 far) 
{
	camera->fov = fov;
	camera->near = near;
	camera->far = far;
  camera->projection_matrix = mat4_perspective(fov, aspect, near, far);
  camera->view_matrix = mat4_translate(V3_ZERO);
}

void camera_destroy(Camera *camera) 
{ 
	memset(camera, 0, sizeof(Camera)); 
}

void camera_update(Camera *camera)
{
  camera->view_matrix = mat4_translate(camera->position);
}

void camera_on_resize(Camera *camera, Vec4 viewport)
{
	f32 aspect = viewport.w / viewport.z;
  camera->projection_matrix = mat4_perspective(camera->fov, aspect, camera->near, camera->far);
}

Mat4 camera_get_projection_matrix(Camera *camera) 
{ 
	return camera->projection_matrix; 
}

Mat4 camera_get_view_matrix(Camera *camera) 
{ 
	return camera->view_matrix; 
}
