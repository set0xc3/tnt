#if !defined(TNT_CAMERA_H)
#define TNT_CAMERA_H

#include "tnt_types.h"
#include "tnt_math.h"

typedef struct Camera Camera;
struct Camera
{
	Vec3F32 position;
	Vec3F32 front;
	Vec3F32 up;
	Vec3F32 right;
	Vec3F32 world_up;

	f32 yaw;
	f32 pitch;
	f32 aspect;
};

void camera_create(Camera *ctx, Vec3F32 position, Vec3F32 up, f32 yaw, f32 pitch, f32 aspect);
void camera_destroy(Camera *ctx);
void camera_vectors_update(Camera *ctx);
Vec3F32 camera_position_get(Camera *ctx);
Vec3F32 camera_forward_get(Camera *ctx);
// f32 	  *camera_view_matrix_get(Camera *ctx);
// mat4 	  camera_project_matrix(Camera *ctx);

#endif // TNT_CAMERA_H
