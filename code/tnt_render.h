#if !defined(TNT_RENDER_H)
#define TNT_RENDER_H

#include "tnt_base_types.h"
#include "tnt_camera.h"
#include "tnt_entity.h"
#include "tnt_math.h"
#include "tnt_os.h"
#include "tnt_render_types.h"

typedef struct RenderState RenderState;
struct RenderState {
  R_ShaderHandle shader_3d;
  R_ShaderHandle shader_2d;
  R_ShaderHandle shader_grid;
};

void render_init(RenderState *render, OS_Window *window);
void render_begin(RenderState *render, OS_Window *window);
void render_flush(RenderState *render, Entity *entity);
void render_end(RenderState *render, OS_Window *window);

void render_create_model(RenderState *render, R_ModelStatic enum_model,
                         R_Model *out_model);

void draw_line(RenderState *render, Vec2 v1, Vec2 v2, Vec4 color);
void draw_rect(RenderState *render, Vec2 position, Vec2 size, Vec4 color);
void draw_cube(RenderState *render, Vec3 position, Vec2 size, Vec4 color);

#endif  // TNT_RENDER_H
