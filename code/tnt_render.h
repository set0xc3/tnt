#if !defined(TNT_RENDER_H)
#define TNT_RENDER_H

#include "tnt_types.h"
#include "tnt_string.h"
#include "tnt_vector.h"
#include "tnt_render_types.h"

typedef struct TNT_RenderAPI TNT_RenderAPI;
struct TNT_RenderAPI {
  char *version;
  void (*init)(R_Window *window);
  void (*destroy)(R_Window *window);
  void (*begin)(R_Window *window, R_Context *context, V4F32 viewport);
  void (*flush)(R_Window *window, R_Mesh *mesh);
  void (*end)(R_Window *window);
  u32  (*shader_load)(String8 vs_path, String8 fs_path);
  void (*shader_bind)(u32 id);
	u32  (*index_buffer_create)(void *buffer, u64 size);
	void (*index_buffer_bind)(u32 id);
	u32  (*vertex_buffer_create)(void *buffer, u64 size);
	void (*vertex_buffer_bind)(u32 id);
	void (*vertex_buffer_update)(void *buffer, u64 size);
	u32  (*frame_buffer_create)(void *buffer, u64 size);
	void (*frame_buffer_bind)(u32 id);
	u32  (*render_buffer_create)(u32 width, u32 height);
	void (*render_buffer_bind)(u32 id);
	u32  (*vertex_array_create)(u32 vbo_id, void *buffer, u64 size);
	void (*vertex_array_bind)(u32 id);
};

typedef struct TNT_Render TNT_Render;
struct TNT_Render {
  void *handle;
  TNT_RenderAPI *api;
};

b8   render_load(TNT_Render *ctx, String8 path);
void render_unload(TNT_Render *ctx);

#endif // TNT_RENDER_H
