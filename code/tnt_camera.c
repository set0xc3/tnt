#include "tnt_camera.h"

void camera_create(Camera *ctx, Vec3 position, Vec3 up, f32 yaw, f32 pitch, f32 aspect)
{
	ctx->position = position;
	ctx->up = up;
	ctx->yaw = yaw;
	ctx->pitch = pitch;
	ctx->aspect = aspect;
}

void camera_destroy(Camera *ctx)
{
	memset(ctx, 0, sizeof(Camera));
}

