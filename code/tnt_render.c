#include "tnt_render.h"
#include "tnt_os.h"
#include "tnt_types.h"
#include "tnt_logger.h"

#define MAX_QUAD_COUNT 1000
#define MAX_VERTEX_COUNT MAX_QUAD_COUNT * 4
#define MAX_INDEX_COUNT MAX_QUAD_COUNT * 6

b8 render_load(TNT_Render *ctx, R_Window window_handle, String8 path)
{
	ctx->handle = os_library_load(path);
	if (!ctx->handle)
	{
		LOG_ERROR("[Render]: Failed load library");
		ASSERT(true);
		return false;
	}
	ctx->api = os_library_load_symbol(ctx->handle, str8("api"));
	if (!ctx->api)
	{
		LOG_ERROR("[Render]: Failed load symbol library");
		ASSERT(true);
		return false;
	}
	ctx->api->init(window_handle);
	return true;
}

void render_unload(TNT_Render *ctx)
{
	os_library_unload(ctx->handle);
}

void render_init(TNT_Render *ctx)
{
	ctx->debug_shader = ctx->api->shader_load(
		str8("./assets/shaders/debug_vs.glsl"),
		str8("./assets/shaders/debug_fs.glsl"),
		str8(""));

	ctx->default_shader = ctx->api->shader_load(
		str8("./assets/shaders/default_vs.glsl"),
		str8("./assets/shaders/default_fs.glsl"),
		str8(""));

	// TODO(duck): 0x1406 = GL_FLOAT
	R_VertexAttribs debug_attribs[] = {
		{2, 0x1406, sizeof(R_Vertex2D), GetMember(R_Vertex2D, position)},
		{4, 0x1406, sizeof(R_Vertex2D), GetMember(R_Vertex2D, color)},
	};

	R_VertexAttribs default_attribs[] = {
		{3, 0x1406, sizeof(R_Vertex3D), GetMember(R_Vertex3D, position)},
		{4, 0x1406, sizeof(R_Vertex3D), GetMember(R_Vertex3D, color)},
	};

	ctx->default_vbo = ctx->api->vertex_buffer_create(0,  MAX_QUAD_COUNT);
	ctx->default_vao = ctx->api->vertex_array_create(ctx->default_vbo, default_attribs, ArrayCount(default_attribs));

	ctx->debug_vbo = ctx->api->vertex_buffer_create(0,  MAX_QUAD_COUNT);
	ctx->debug_vao = ctx->api->vertex_array_create(ctx->debug_vbo, debug_attribs, ArrayCount(debug_attribs));
}

void draw_line(TNT_Render *ctx, Vec2 v1, Vec2 v2, Vec4 color)
{
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

void draw_rectangle(TNT_Render *ctx, Vec2 position, Vec2 size, Vec4 color)
{
	f32 x = position.x;
	f32 y = position.y;
	f32 w = size.x;
	f32 h = size.y;
	R_Vertex2D vertices[] = {
		{v2(x, y), color},
		{v2(x + w, y), color},
		{v2(x + w, y + h), color},

		{v2(x + w, y + h), color},
		{v2(x, y + h), color},
		{v2(x, y), color},
	};
	ctx->api->shader_bind(ctx->debug_shader);
	ctx->api->vertex_buffer_bind(ctx->debug_vbo);
	ctx->api->vertex_buffer_update(vertices, sizeof(vertices));
	ctx->api->vertex_array_bind(ctx->debug_vao);
	ctx->api->flush(DRAWING_MODE_TRIANGLES, ArrayCount(vertices));
}

void draw_cube(TNT_Render *ctx, Vec3 position, Vec2 size, Vec4 color)
{
	f32 x = position.x;
	f32 y = position.y;
	f32 z = position.y;
	f32 w = size.x;
	f32 h = size.y;
	R_Vertex3D vertices[] = {
		{v3(-0.5f, -0.5f, -0.5f), color},
		{v3(0.5f, -0.5f, -0.5f), color},
		{v3(0.5f, 0.5f, -0.5f), color},
		{v3(0.5f, 0.5f, -0.5f), color},
		{v3(-0.5f, 0.5f, -0.5f), color},
		{v3(-0.5f, -0.5f, -0.5f), color},

		{v3(-0.5f, -0.5f,  0.5f), color},
		{v3(0.5f, -0.5f,  0.5f), color},
		{v3(0.5f,  0.5f,  0.5f), color},
		{v3(0.5f,  0.5f,  0.5f), color},
		{v3(-0.5f,  0.5f,  0.5f), color},
		{v3(-0.5f, -0.5f,  0.5f), color},

		{v3(-0.5f,  0.5f,  0.5f), color},
		{v3(-0.5f,  0.5f, -0.5f), color},
		{v3(-0.5f, -0.5f, -0.5f), color},
		{v3(-0.5f, -0.5f, -0.5f), color},
		{v3(-0.5f, -0.5f,  0.5f), color},
		{v3(-0.5f,  0.5f,  0.5f), color},

		{v3(0.5f,  0.5f,  0.5f), color},
		{v3(0.5f,  0.5f, -0.5f), color},
		{v3(0.5f, -0.5f, -0.5f), color},
		{v3(0.5f, -0.5f, -0.5f), color},
		{v3(0.5f, -0.5f,  0.5f), color},
		{v3(0.5f,  0.5f,  0.5f), color},
		
		{v3(-0.5f, -0.5f, -0.5f), color},
		{v3(0.5f, -0.5f, -0.5f), color},
		{v3(0.5f, -0.5f,  0.5f), color},
		{v3(0.5f, -0.5f,  0.5f), color},
		{v3(-0.5f, -0.5f,  0.5f), color},
		// {v3(-0.5f, -0.5f, -0.5f), color},
	};
	ctx->api->shader_bind(ctx->default_shader);
	ctx->api->vertex_buffer_bind(ctx->default_vbo);
	ctx->api->vertex_buffer_update(vertices, sizeof(vertices));
	ctx->api->vertex_array_bind(ctx->default_vao);
	ctx->api->flush(DRAWING_MODE_TRIANGLES, ArrayCount(vertices));
}
