#include "tnt_render.h"
#include "tnt_camera.h"
#include "tnt_os.h"
#include "tnt_types.h"

#include "tnt_render_internal.c"

#define MAX_VERTEX_COUNT 1000
#define MAX_INDEX_COUNT 1000

void render_init(Render_State *render, OS_Window *window)
{
	gl_init(window->handle);

	render->shader_2d = gl_shader_load(
		str8("./assets/shaders/2d_vs.glsl"),
		str8("./assets/shaders/2d_fs.glsl"),
		str8(""));

	render->shader_3d = gl_shader_load(
		str8("./assets/shaders/3d_vs.glsl"),
		str8("./assets/shaders/3d_fs.glsl"),
		str8(""));

	// TODO(duck): 0x1406 = GL_FLOAT
	
	R_VertexAttribs attribs_2d[] = {
		{2, 0x1406, sizeof(R_Vertex2D), GetMember(R_Vertex2D, position)},
		{4, 0x1406, sizeof(R_Vertex2D), GetMember(R_Vertex2D, color)},
	};

	R_VertexAttribs attribs_3d[] = {
		{3, 0x1406, sizeof(R_Vertex3D), GetMember(R_Vertex3D, position)},
		{4, 0x1406, sizeof(R_Vertex3D), GetMember(R_Vertex3D, color)},
	};

	render->vbo_2d = gl_vertex_buffer_create(0,  MAX_VERTEX_COUNT);
	render->vao_2d = gl_vertex_array_create(render->vbo_2d, attribs_2d, ArrayCount(attribs_2d));

	render->vbo_3d = gl_vertex_buffer_create(0,  MAX_VERTEX_COUNT);
	render->vao_3d = gl_vertex_array_create(render->vbo_3d, attribs_3d, ArrayCount(attribs_3d));
}

void render_begin(Render_State *render, OS_Window *window, Camera *camera, R_Shader shader)
{
	Mat4 projection_matrix = camera_get_projection_matrix(camera);
	Mat4 view_matrix = camera_get_view_matrix(camera);
  gl_begin(window->handle, window->render, v4(0.0f, 0.0f, window->width, window->height));
	gl_uniform_mat4_set(shader, str8("projection"), *projection_matrix.m);
	gl_uniform_mat4_set(shader, str8("view"), *view_matrix.m);
}

void render_flush(Render_State *render, Entity *entity)
{
	Mat4 model_matrix = mat4_identity();
	model_matrix = mat4_mul_mat4(model_matrix, mat4_translate(entity->position)); 
	gl_uniform_mat4_set(render->shader_3d, str8("model"), *model_matrix.m);

	gl_shader_bind(render->shader_3d);
	gl_vertex_buffer_bind(render->vbo_3d);
	gl_vertex_buffer_update(entity->mesh->vertices, sizeof(R_Vertex3D) * entity->mesh->vertices_count);
	gl_vertex_array_bind(render->vao_3d);
	gl_flush(DRAWING_MODE_TRIANGLES, entity->mesh->vertices_count);
}

void render_end(Render_State *render, OS_Window *window)
{
  gl_end(window->handle);
}

void draw_line(Render_State *render, Vec2 v1, Vec2 v2, Vec4 color)
{
	R_Vertex2D vertices[] = {
		{v1, color},
		{v2, color},
	};

	Mat4 model_matrix = mat4_identity();
	model_matrix = mat4_mul_mat4(model_matrix, mat4_translate(v3(v1.x, v1.y, 0.0f))); 

	gl_uniform_mat4_set(render->shader_3d, str8("model"), *model_matrix.m);
	gl_shader_bind(render->shader_2d);
	gl_vertex_buffer_bind(render->vbo_2d);
	gl_vertex_buffer_update(vertices, sizeof(vertices));
	gl_vertex_array_bind(render->vao_2d);
	gl_flush(DRAWING_MODE_LINES, ArrayCount(vertices));
}

void draw_rect(Render_State *render, Vec2 position, Vec2 size, Vec4 color)
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

	gl_shader_bind(render->shader_2d);
	gl_vertex_buffer_bind(render->vbo_2d);
	gl_vertex_buffer_update(vertices, sizeof(vertices));
	gl_vertex_array_bind(render->vao_2d);

	Mat4 model_matrix = mat4_identity();
	model_matrix = mat4_mul_mat4(model_matrix, mat4_translate(v3(position.x, position.y, 0.0f))); 
	model_matrix = mat4_mul_mat4(model_matrix, mat4_scale(v3(size.x, size.y, 0.0f))); 
	gl_uniform_mat4_set(render->shader_3d, str8("model"), *model_matrix.m);

	gl_flush(DRAWING_MODE_TRIANGLES, ArrayCount(vertices));
}

void draw_cube(Render_State *render, Vec3 position, Vec2 size, Vec4 color)
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
	gl_shader_bind(render->shader_3d);
	gl_vertex_buffer_bind(render->vbo_3d);
	gl_vertex_buffer_update(vertices, sizeof(vertices));
	gl_vertex_array_bind(render->vao_3d);
	gl_flush(DRAWING_MODE_TRIANGLES, ArrayCount(vertices));
}
