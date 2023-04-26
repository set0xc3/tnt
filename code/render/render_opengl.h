#if !defined(RENDER_OPENGL_H)
#define RENDER_OPENGL_H

#include "tnt_types.h"
#include "tnt_string.h"
#include "tnt_render_types.h"

internal void gl_init(R_Window *window);
internal void gl_destroy(R_Window *window);
internal void gl_begin(R_Window *window, R_Context *context, Vec4 viewport);
internal void gl_flush(u32 drawing_mode, u64 vertex_count);
internal void gl_end(R_Window *window);
internal void gl_window_select(R_Window *window, R_Context *ctx);
internal u32 	gl_shader_load(String8 vs_path, String8 fs_path, String8 gs_path);
internal void gl_shader_bind(u32 id);
internal u32 	gl_index_buffer_create(void *buffer, u64 size);
internal void gl_index_buffer_bind(u32 id);
internal u32 	gl_vertex_buffer_create(void *buffer, u64 size);
internal void gl_vertex_buffer_bind(u32 id);
internal void gl_vertex_buffer_update(void *buffer, u64 size);
internal u32 	gl_frame_buffer_create(void *buffer, u64 size);
internal void gl_frame_buffer_bind(u32 id);
internal u32 	gl_render_buffer_create(u32 width, u32 height);
internal void gl_render_buffer_bind(u32 id);
internal u32 	gl_vertex_array_create(u32 vbo_id, R_VertexAttribs *attribs, u32 size);
internal void gl_vertex_array_bind(u32 id);
internal void gl_uniform_mat4_set(u32 id, String8 name, f32 *mat);

#endif // RENDER_OPENGL_H
