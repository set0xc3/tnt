#include "tnt_render.h"
#include "tnt_os.h"
#include "tnt_types.h"
#include "tnt_logger.h"

#define MAX_QUAD_COUNT 1000
#define MAX_VERTEX_COUNT MAX_QUAD_COUNT * 4
#define MAX_INDEX_COUNT MAX_QUAD_COUNT * 6

b8 render_load(TNT_Render *ctx, R_Window window_handle, String8 path) {
  ctx->handle = os_library_load(path);
  if (!ctx->handle) {
		LOG_ERROR("[Render]: Failed load library");
		ASSERT(true);
    return false;
  }
  ctx->api = os_library_load_symbol(ctx->handle, str8("api"));
  if (!ctx->api) {
		LOG_ERROR("[Render]: Failed load symbol library");
		ASSERT(true);
    return false;
  }
  ctx->api->init(window_handle);
  return true;
}

void render_unload(TNT_Render *ctx) { 
	os_library_unload(ctx->handle); 
}

void debug_render_init(TNT_Render *ctx) {
  ctx->debug_shader = ctx->api->shader_load(
		str8("./assets/shaders/debug_vs.glsl"),
  	str8("./assets/shaders/debug_fs.glsl"),
		str8(""));

	// TODO(duck): 0x1406 = GL_FLOAT
	R_VertexAttribs attribs[] = {
		{2, 0x1406, sizeof(R_Vertex2D), GetMember(R_Vertex2D, position)},
		{4, 0x1406, sizeof(R_Vertex2D), GetMember(R_Vertex2D, color)},
	};

  ctx->debug_vbo = ctx->api->vertex_buffer_create(0, 1000);
  ctx->debug_vao = ctx->api->vertex_array_create(ctx->debug_vbo, attribs, ArrayCount(attribs));
}

void debug_draw_line_2d(TNT_Render *ctx, Vec2F32 v1, Vec2F32 v2, Vec4F32 color) {
	R_Vertex2D vertices[] = {
		{v1, color},
		{v2, color},
	};
	ctx->api->shader_bind(ctx->debug_shader);
  ctx->api->vertex_buffer_bind(ctx->debug_vbo);
  ctx->api->vertex_buffer_update(vertices, sizeof(vertices));
	ctx->api->vertex_array_bind(ctx->debug_vao);
	ctx->api->flush(DRAWING_MODE_LINES, ArrayCount(vertices));
}

void debug_draw_rectangle_2d(TNT_Render *ctx, Vec2F32 position, Vec2F32 size, Vec4F32 color) {
	f32 x = position.x;
	f32 y = position.y;
	f32 w = size.x;
	f32 h = size.y;
	R_Vertex2D vertices[] = {
  	{v2f32(x,y), color},
  	{v2f32(x+w,y), color},
  	{v2f32(x+w,y+h), color},

  	{v2f32(x+w,y+h), color},
  	{v2f32(x,y+h), color},
  	{v2f32(x,y), color},
	};
	ctx->api->shader_bind(ctx->debug_shader);
  ctx->api->vertex_buffer_bind(ctx->debug_vbo);
  ctx->api->vertex_buffer_update(vertices, sizeof(vertices));
	ctx->api->vertex_array_bind(ctx->debug_vao);
	ctx->api->flush(DRAWING_MODE_TRIANGLES, ArrayCount(vertices));
}
