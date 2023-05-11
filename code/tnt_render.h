#if !defined(TNT_RENDER_H)
#define TNT_RENDER_H

#include "tnt_base_types.h"
#include "tnt_camera.h"
#include "tnt_math.h"
#include "tnt_os.h"
#include "tnt_render_types.h"

typedef struct RenderState RenderState;
struct RenderState {
  R_ShaderHandle shader_3d;
  R_ShaderHandle shader_2d;
  R_ShaderHandle shader_grid;

  u32 quad_vbo, quad_veo, quad_vao;
  R_Vertex2D quad_buffer[1000];
  u64 quad_buffer_idx;
};

void render_init(RenderState *render, OS_Window *window);
void render_begin(RenderState *render, OS_Window *window);
void render_end(RenderState *render, OS_Window *window);

void render_create_model(RenderState *render, R_ModelStatic enum_model,
                         R_Model *out_model);

void render_draw_line(RenderState *render, Vec2 point1, Vec2 point2,
                      Vec4 color);
void render_draw_rect(RenderState *render, Vec4 rect, Vec4 color);

#endif  // TNT_RENDER_H
