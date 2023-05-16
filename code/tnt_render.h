#if !defined(TNT_RENDER_H)
#define TNT_RENDER_H

#include "tnt_base_types.h"
#include "tnt_camera.h"
#include "tnt_math.h"
#include "tnt_os.h"
#include "tnt_render_types.h"

#define QUAD_MAX 1000
#define QUAD_BUFFER_CAPASITY QUAD_MAX * 6

#define RENDER_STATE_STACK_SIZE 256

typedef struct RenderState {
  b32 depth_is_enabled;
  b32 blend_is_enabled;
} RenderState;

typedef struct RenderContext {
  RenderState *current_state;
  RenderState state_stack[RENDER_STATE_STACK_SIZE];
  u64 state_stack_idx;

  R_ShaderHandle shader_3d;
  R_ShaderHandle shader_2d;
  R_ShaderHandle shader_grid;

  u32 quad_vbo, quad_veo, quad_vao;
  R_Vertex2D quad_vertices[QUAD_BUFFER_CAPASITY];
  u64 quad_buffer_idx;

} RenderContext;

void render_init(RenderContext *render, OS_Window *window);
void render_begin(RenderContext *render, OS_Window *window);
void render_end(RenderContext *render, OS_Window *window);

void render_push_state(RenderContext *render);
void render_pop_state(RenderContext *render);

void render_set_depth_state(RenderContext *render, b32 enabled);

void render_create_model(RenderContext *render, R_ModelStatic enum_model,
                         R_Model *out_model);

void render_draw_line(RenderContext *render, Vec2 point1, Vec2 point2,
                      Vec4 color);
void render_draw_rect(RenderContext *render, Vec2 position, Vec2 size,
                      Vec4 color);

#endif  // TNT_RENDER_H
