#include "tnt_camera.h"
#include "tnt_math.h"

void camera_on_resize(Camera *camera, Vec4 viewport)
{
	f32 aspect = viewport.w / viewport.z;
  camera->projection_matrix = mat4_perspective(camera->fov, aspect, camera->near, camera->far);
}

void camera_create(Camera *camera, f32 fov, f32 aspect, f32 near, f32 far) 
{
	camera->position = v3(0.0f, 0.0f, -10.0f);
	camera->rotation = V3_ZERO;
	camera->scale = V3_ONE;

	camera->move_speed = 8.0f;
	camera->rotate_speed = 1.0f;

	camera->fov = fov;
	camera->near = near;
	camera->far = far;
  camera->projection_matrix = mat4_perspective(fov, aspect, near, far);
}

void camera_destroy(Camera *camera) 
{ 
	memset(camera, 0, sizeof(Camera)); 
}

void camera_update(Camera *camera, OS_Input *input, f32 dt)
{
	if (os_input_key_pressed(input, OS_KEYCODE_W))
	{
		camera->position.z += camera->move_speed * dt;
	}
	if (os_input_key_pressed(input, OS_KEYCODE_S))
	{
		camera->position.z -= camera->move_speed * dt;
	}
	if (os_input_key_pressed(input, OS_KEYCODE_A))
	{
		camera->position.x += camera->move_speed * dt;
	}
	if (os_input_key_pressed(input, OS_KEYCODE_D))
	{
		camera->position.x -= camera->move_speed * dt;
	}
	if (os_input_key_pressed(input, OS_KEYCODE_Q))
	{
		camera->position.y += camera->rotate_speed * dt;
	}
	if (os_input_key_pressed(input, OS_KEYCODE_E))
	{
		camera->position.y -= camera->rotate_speed * dt;
	}
	camera->view_matrix = mat4_look_at(v3(0.0f, 0.0f, 1.0f), v3(0.0f, 0.0f, 0.0f), v3(0.0f, 1.0f, 0.0f));
	camera->view_matrix = mat4_mul_mat4(camera->view_matrix, mat4_translate(camera->position));
	camera->view_matrix = mat4_mul_mat4(camera->view_matrix, mat4_rotate(camera->rotation.y, v3(0.0f, 1.0f, 0.0f)));
	camera->view_matrix = mat4_mul_mat4(camera->view_matrix, mat4_scale(camera->scale));

	// LOG_DEBUG("camera: (%f, %f, %f)", camera->position.x, camera->position.y, camera->position.z);
}

Mat4 camera_get_projection_matrix(Camera *camera) 
{ 
	return camera->projection_matrix; 
}

Mat4 camera_get_view_matrix(Camera *camera) 
{ 
	return camera->view_matrix; 
}
