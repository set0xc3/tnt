#if !defined(TNT_RENDER_H)
#define TNT_RENDER_H

#include "tnt_types.h"
#include "tnt_math.h"
#include "tnt_render_types.h"
#include "tnt_camera.h"
#include "tnt_os.h"
#include "tnt_entity.h"

typedef struct Render_State
{
	u32 vbo_3d;
	u32 vao_3d;
	R_Shader shader_3d;

	u32 vbo_2d;
	u32 vao_2d;
	R_Shader shader_2d;
} Render_State;

void render_init(Render_State *render, OS_Window *window);
void render_begin(Render_State *render, OS_Window *window, Camera *camera, R_Shader shader);
void render_flush(Render_State *render, Entity *entity);
void render_end(Render_State *render, OS_Window *window);

void render_add_line();

void draw_line(Render_State *render, Vec2 v1, Vec2 v2, Vec4 color);
void draw_rect(Render_State *render, Vec2 position, Vec2 size, Vec4 color);
void draw_cube(Render_State *render, Vec3 position, Vec2 size, Vec4 color);

#endif // TNT_RENDER_H
