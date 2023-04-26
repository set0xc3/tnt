#if !defined(TNT_CAMERA_H)
#define TNT_CAMERA_H

#include "tnt_types.h"
#include "tnt_math.h"

typedef struct Camera Camera;
struct Camera
{
	Vec3 position;
	Vec3 front;
	Vec3 up;
	Vec3 right;
	Vec3 world_up;

	f32 yaw;
	f32 pitch;
	f32 aspect;
};

void camera_create(Camera *ctx, Vec3 position, Vec3 up, f32 yaw, f32 pitch, f32 aspect);
void camera_destroy(Camera *ctx);

#endif // TNT_CAMERA_H
