#include "tnt_scene.h"
#include "tnt_render_types.h"
#include "tnt_logger.h"

void scene_on_resize(Scene *scene, Vec4 viewport)
{
	camera_on_resize(scene->camera, viewport);
}

void scene_init(Scene *scene, TNT_MemoryArena *arena)
{
	scene->arena = arena;
  scene->entities = push_array_zero(arena, Entity, ENTITIES_CAPASITY);
	scene->camera = push_struct_zero(arena, Camera);

	camera_create(scene->camera, 45.0f, 0.5625f, 0.1f, 1000.0f);

	Vec4 color = COLOR_GREEN_DARK;
	R_Vertex3D cube_vertices[] = {
		{v3(-1.0f, -1.0f, -1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(1.0f, -1.0f, -1.0f), color},
		{v3(1.0f, 1.0f, -1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(1.0f, 1.0f, -1.0f), color},
		{v3(-1.0f, 1.0f, -1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(-1.0f, -1.0f, -1.0f), color},

		{v3(-1.0f, -1.0f,  1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(1.0f, -1.0f,  1.0f), color},
		{v3(1.0f,  1.0f,  1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(1.0f,  1.0f,  1.0f), color},
		{v3(-1.0f,  1.0f,  1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(-1.0f, -1.0f,  1.0f), color},

		{v3(-1.0f,  1.0f,  1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(-1.0f,  1.0f, -1.0f), color},
		{v3(-1.0f, -1.0f, -1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(-1.0f, -1.0f, -1.0f), color},
		{v3(-1.0f, -1.0f,  1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(-1.0f,  1.0f,  1.0f), color},

		{v3(1.0f,  1.0f,  1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(1.0f,  1.0f, -1.0f), color},
		{v3(1.0f, -1.0f, -1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(1.0f, -1.0f, -1.0f), color},
		{v3(1.0f, -1.0f,  1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(1.0f,  1.0f,  1.0f), color},
		
		{v3(-1.0f, -1.0f, -1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(1.0f, -1.0f, -1.0f), color},
		{v3(1.0f, -1.0f,  1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(1.0f, -1.0f,  1.0f), color},
		{v3(-1.0f, -1.0f,  1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(-1.0f, -1.0f, -1.0f), color},
	};

	Entity *ent = scene_push_entity(scene, v3(0.0f, 0.0f, 0.0f), V3_ONE);
	ent->mesh = push_struct_zero(arena, R_Mesh);
	ent->mesh->vertices = push_array_zero(arena, R_Vertex3D, ArrayCount(cube_vertices));
	memcpy(ent->mesh->vertices, cube_vertices, sizeof(cube_vertices));
	ent->mesh->vertices_count = ArrayCount(cube_vertices);

	ent = scene_push_entity(scene, v3(0.0f, 2.0f, 0.0f), V3_ONE);
	ent->mesh = push_struct_zero(arena, R_Mesh);
	ent->mesh->vertices = push_array_zero(arena, R_Vertex3D, ArrayCount(cube_vertices));
	memcpy(ent->mesh->vertices, cube_vertices, sizeof(cube_vertices));
	ent->mesh->vertices_count = ArrayCount(cube_vertices);

}

void scene_update(Scene *scene, OS_Input *input, f32 dt)
{
	camera_update(scene->camera, input, dt);
}

Entity *scene_push_entity(Scene *scene, Vec3 pos, Vec3 scale)
{
	ASSERT(scene->entities_count + 1 > ENTITIES_CAPASITY);

	Entity *ent = scene->entities + scene->entities_count;
	ent->position = pos;
	ent->scale = scale;
	scene->entities_count += 1;
	return ent;
}

Entity *scene_pop_entity(Scene *scene)
{
  ASSERT(scene->entities_count == 0);

	Entity *result = scene->entities + scene->entities_count - 1;
	memset(result, 0, sizeof(Entity));
	scene->entities_count -= 1;

	return result;
}

void scene_remove_entity(Scene *scene, Entity *entity)
{
  ASSERT(scene->entities_count == 0);

	memset(entity, 0, sizeof(Entity));
	scene->entities_count -= 1;
}

Entity *scene_get_entity(Scene *scene, u32 index)
{
  ASSERT(scene->entities_count == 0);

	Entity *ent = scene->entities + index;

	return ent;
}

u32	scene_get_entites_count(Scene *scene)
{
	return scene->entities_count;
}

Camera *scene_get_camera(Scene *scene)
{
	return scene->camera;
}
