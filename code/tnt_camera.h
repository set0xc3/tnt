#if !defined(TNT_CAMERA_H)
#define TNT_CAMERA_H

#include "tnt_types.h"
#include "tnt_vector.h"
#include "tnt_math.h"

typedef struct Camera Camera;
struct Camera {
	Vec3F32 position;
	Vec3F32 target;
	f32 aspect;
};

typedef struct Motion Motion;
struct Motion {
	Vec2F32 orgit;
	Vec2F32 pan;
	f32 dolly;
};

Camera *camera_create(Vec3F32 position, Vec3F32 target, f32 aspect);
void    camera_destroy(Camera *camera);
void    camera_transform_set(Camera *camera, Vec3F32 position, Vec3F32 target);
void    camera_transform_update(Camera *camera, Motion motion);
Vec3F32    camera_position_get(Camera *camera);
Vec3F32    camera_forward_get(Camera *camera);
Mat4 	camera_view_matrix_get(Camera *camera);
Mat4 	camera_project_matrix(Camera *camera);

#endif // TNT_CAMERA_H