#if !defined(TNT_RENDER_H)
#define TNT_RENDER_H

#include "tnt_types.h"
#include "tnt_string.h"
#include "tnt_math.h"
#include "tnt_render_types.h"
#include "tnt_camera.h"
#include "tnt_os.h"

typedef struct TNT_RenderAPI TNT_RenderAPI;
struct TNT_RenderAPI
{
	char *version;
	void (*init)(R_Window *window);
	void (*destroy)(R_Window *window);
	void (*begin)(R_Window *window, R_Context *context, Vec4 viewport);
	void (*flush)(u32 drawing_mode, u64 vertex_count);
	void (*end)(R_Window *window);
	u32  (*shader_load)(String8 vs_path, String8 fs_path, String8 gs_path);
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
	u32  (*vertex_array_create)(u32 vbo_id, R_VertexAttribs *attribs, u32 size);
	void (*vertex_array_bind)(u32 id);
	void (*uniform_mat4_set)(u32 id, String8 name, f32 *mat);
};

typedef struct TNT_Render TNT_Render;
struct TNT_Render
{
	void *handle;
	TNT_RenderAPI *api;

	u32 debug_vbo;
	u32 debug_vao;
	R_Shader debug_shader;

	u32 default_vbo;
	u32 default_vao;
	R_Shader default_shader;
};

b8 	 render_load(TNT_Render *ctx, R_Window *window_handle, String8 path);
void render_unload(TNT_Render *ctx);

void render_init(TNT_Render *ctx);
void render_begin(OS_Window *window, TNT_Render *render, Camera *camera, R_Shader shader);
void render_end(TNT_Render *render, R_Window *window_handle);
void draw_line(TNT_Render *ctx, Vec2 v1, Vec2 v2, Vec4 color);
void draw_rectangle(TNT_Render *ctx, Vec2 position, Vec2 size, Vec4 color);
void draw_cube(TNT_Render *ctx, Vec3 position, Vec2 size, Vec4 color);

#endif // TNT_RENDER_H
