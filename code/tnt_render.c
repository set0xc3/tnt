#include "tnt_render.h"
#include "tnt_camera.h"
#include "tnt_os.h"
#include "tnt_types.h"
#include "tnt_logger.h"

#define MAX_QUAD_COUNT 1000
#define MAX_VERTEX_COUNT MAX_QUAD_COUNT * 4
#define MAX_INDEX_COUNT MAX_QUAD_COUNT * 6

b8 render_load(TNT_Render *render, R_Window *window_handle, String8 path)
{
	render->handle = os_library_load(path);
	if (!render->handle)
	{
		LOG_ERROR("[Render]: Failed load library");
		ASSERT(true);
		return false;
	}
	render->api = os_library_load_symbol(render->handle, str8("api"));
	if (!render->api)
	{
		LOG_ERROR("[Render]: Failed load symbol library");
		ASSERT(true);
		return false;
	}
	render->api->init(window_handle);
	return true;
}

void render_unload(TNT_Render *render)
{
	os_library_unload(render->handle);
}

void render_init(TNT_Render *render)
{
	render->debug_shader = render->api->shader_load(
		str8("./assets/shaders/debug_vs.glsl"),
		str8("./assets/shaders/debug_fs.glsl"),
		str8(""));

	render->default_shader = render->api->shader_load(
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

	render->default_vbo = render->api->vertex_buffer_create(0,  MAX_QUAD_COUNT);
	render->default_vao = render->api->vertex_array_create(render->default_vbo, default_attribs, ArrayCount(default_attribs));

	render->debug_vbo = render->api->vertex_buffer_create(0,  MAX_QUAD_COUNT);
	render->debug_vao = render->api->vertex_array_create(render->debug_vbo, debug_attribs, ArrayCount(debug_attribs));
}

void render_begin(OS_Window *window, TNT_Render *render, Camera *camera, R_Shader shader)
{
	Mat4 projection_matrix = camera_get_projection_matrix(camera);
	Mat4 view_matrix = camera_get_view_matrix(camera);
  render->api->begin(window->handle, window->render, v4(0.0f, 0.0f, window->width, window->height));
	render->api->uniform_mat4_set(shader, str8("projection"), *projection_matrix.m);
	render->api->uniform_mat4_set(shader, str8("view"), *view_matrix.m);
}

void render_flush(TNT_Render *render, R_Mesh *mesh)
{
	render->api->shader_bind(render->default_shader);
	render->api->vertex_buffer_bind(render->default_vbo);
	render->api->vertex_buffer_update(mesh->vertices, sizeof(R_Vertex3D) * mesh->vertices_count);
	render->api->vertex_array_bind(render->default_vao);
	render->api->flush(DRAWING_MODE_TRIANGLES, mesh->vertices_count);
}

void render_end(TNT_Render *render, R_Window *window_handle)
{
  render->api->end(window_handle);
}

void draw_line(TNT_Render *render, Vec2 v1, Vec2 v2, Vec4 color)
{
	R_Vertex2D vertices[] = {
		{v1, color},
		{v2, color},
	};
	render->api->shader_bind(render->debug_shader);
	render->api->vertex_buffer_bind(render->debug_vbo);
	render->api->vertex_buffer_update(vertices, sizeof(vertices));
	render->api->vertex_array_bind(render->debug_vao);
	render->api->flush(DRAWING_MODE_LINES, ArrayCount(vertices));
}

void draw_rect(TNT_Render *render, Vec2 position, Vec2 size, Vec4 color)
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

	render->api->shader_bind(render->debug_shader);
	render->api->vertex_buffer_bind(render->debug_vbo);
	render->api->vertex_buffer_update(vertices, sizeof(vertices));
	render->api->vertex_array_bind(render->debug_vao);

	Mat4 model_matrix = mat4_identity();
	model_matrix = mat4_mul_mat4(model_matrix, mat4_translate(v3(position.x, position.y, 0.0f))); 
	render->api->uniform_mat4_set(render->default_shader, str8("model"), *model_matrix.m);

	render->api->flush(DRAWING_MODE_TRIANGLES, ArrayCount(vertices));
}

void draw_cube(TNT_Render *render, Vec3 position, Vec2 size, Vec4 color)
{
	f32 x = position.x;
	f32 y = position.y;
	f32 z = position.y;
	f32 w = size.x;
	f32 h = size.y;
	R_Vertex3D vertices[] = {
		{v3(-1.0f, -1.0f, -1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(1.0f, -1.0f, -1.0f), color},
		{v3(1.0f, 1.0f, -1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(1.0f, 1.0f, -1.0f), color},
		{v3(-1.0f, 1.0f, -1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(-1.0f, -1.0f, -1.0f), color},

		{v3(-1.0f, -1.0f,  1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(1.0f, -1.0f,  1.0f), color},
		{v3(1.0f,  1.0f,  1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(1.0f,  1.0f,  1.0f), color},
		{v3(-1.0f,  1.0f,  1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(-1.0f, -1.0f,  1.0f), color},

		{v3(-1.0f,  1.0f,  1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(-1.0f,  1.0f, -1.0f), color},
		{v3(-1.0f, -1.0f, -1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(-1.0f, -1.0f, -1.0f), color},
		{v3(-1.0f, -1.0f,  1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(-1.0f,  1.0f,  1.0f), color},

		{v3(1.0f,  1.0f,  1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(1.0f,  1.0f, -1.0f), color},
		{v3(1.0f, -1.0f, -1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(1.0f, -1.0f, -1.0f), color},
		{v3(1.0f, -1.0f,  1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(1.0f,  1.0f,  1.0f), color},
		
		{v3(-1.0f, -1.0f, -1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(1.0f, -1.0f, -1.0f), color},
		{v3(1.0f, -1.0f,  1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(1.0f, -1.0f,  1.0f), color},
		{v3(-1.0f, -1.0f,  1.0f), v4(1.0f, 1.0f, 1.0f, 1.0f)},
		{v3(-1.0f, -1.0f, -1.0f), color},
	};
	render->api->shader_bind(render->default_shader);
	render->api->vertex_buffer_bind(render->default_vbo);
	render->api->vertex_buffer_update(vertices, sizeof(vertices));
	render->api->vertex_array_bind(render->default_vao);
	render->api->flush(DRAWING_MODE_TRIANGLES, ArrayCount(vertices));
}
