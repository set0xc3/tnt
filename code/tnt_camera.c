#include "tnt_camera.h"

void camera_create(Camera *ctx, Vec3F32 position, Vec3F32 up, f32 yaw, f32 pitch, f32 aspect)
{
	ctx->position = position;
	ctx->up 	    = up;
	ctx->yaw 	    = yaw;
	ctx->pitch    = pitch;
	ctx->aspect 	= aspect;
}

void camera_destroy(Camera *ctx)
{
	memset(ctx, 0, sizeof(Camera));
}

void camera_vectors_update(Camera *ctx)
{
	
}

Vec3F32 camera_position_get(Camera *ctx)
{
	return ctx->position;
}

Vec3F32 camera_forward_get(Camera *ctx)
{
	return (Vec3F32){0}; 
}

// f32 *camera_view_matrix_get(Camera *ctx)
// {
// 	f32 *result = 0;
// 	Vec3F32 center = v3f32_add(ctx->position, ctx->front);
// 	glmc_lookat(ctx->position.v, center.v, ctx->up.v, *(mat4*)result);
// 	return result;
// }

// mat4 camera_project_matrix(Camera *ctx)
// {
// }

