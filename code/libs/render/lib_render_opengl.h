#if !defined(LIB_RENDER_OPENGL_H)
#define LIB_RENDER_OPENGL_H

#include "tnt_types.h"
#include "tnt_string.h"
#include "tnt_render_types.h"

internal void gl_init(R_Window *window);
internal void gl_destroy(R_Window *window);
internal void gl_begin(R_Window *window, R_Context *context, V4F32 viewport);
internal void gl_flush(R_Window *window);
internal void gl_end(R_Window *window);
internal void gl_window_select(R_Window *window, R_Context *ctx);
internal u32  gl_shader_load(String8 vs_path, String8 fs_path);

#endif // LIB_RENDER_OPENGL_H
