#include "tnt_application.h"
#include "tnt_logger.h"
#include "tnt_os.h"
#include "tnt_render_types.h"
#include "tnt_string.h"
#include "tnt_vector.h"

#define MAX_QUAD_COUNT 1000
#define MAX_VERTEX_COUNT MAX_QUAD_COUNT * 4
#define MAX_INDEX_COUNT MAX_QUAD_COUNT * 6

typedef struct Entity Entity;
struct Entity {
	V3F32 position;
	V3F32 scale;
	R_Mesh *mesh;
};

R_Mesh r_quad_mesh_craete() {
  R_VertexData v[] = {
		{v3(V3F32, -0.5f, -0.5f, 0.0f), v4(V4F32, 1,0,1,1), v2(V2F32, 0,0)},
 		{v3(V3F32, 0.5f, -0.5f, 0.0f), v4(V4F32, 1,0,1,1), v2(V2F32, 0,0)},
		{v3(V3F32, 0.0f, 0.5f, 0.0f), v4(V4F32, 1,0,1,1), v2(V2F32, 0,0)},
	};

  R_Mesh mesh = {0};
	mesh.vertices = v;
	mesh.vertex_count = ArrayCount(v);
  return mesh;
}

ApplicationState ctx = {0};

void application_init(void) {
  ctx.input  = malloc(sizeof(OS_Input));
  ctx.window = malloc(sizeof(OS_Window));
  ctx.render = malloc(sizeof(Render));

  os_window_open(ctx.window, "Window", 1920, 1080, 0, 0);
  os_window_set_event_callback(ctx.window, application_on_event);

  if (render_load(ctx.render, str8("./librender_opengl"))) {
    LOG_INFO("OpenGL Loaded:");
    LOG_INFO("  Version: %s", ctx.render->api->version);
    ctx.render->api->init(ctx.window->handle);
  }
}

void application_run(void) {
	Entity entites[1000] = {0};
	u32 entity_count = 0;

  R_VertexData v[] = {
		{v3(V3F32, 0.0f, 0.0f, 0.0f), v4(V4F32, 1,0,1,1), v2(V2F32, 0.0f, 0.0f)},
 		{v3(V3F32, 0.5f, 0.0f, 0.0f), v4(V4F32, 1,0,1,1), v2(V2F32, 0.5f, 0.0f)},
		{v3(V3F32, 0.5f, 0.5f, 0.0f), v4(V4F32, 1,0,1,1), v2(V2F32, 0.5f, 0.5f)},

		{v3(V3F32, 0.5f, 0.5f, 0.0f), v4(V4F32, 1,0,1,1), v2(V2F32, 0.5f, 0.5f)},
 		{v3(V3F32, 0.0f, 0.5f, 0.0f), v4(V4F32, 1,0,1,1), v2(V2F32, 0.0f, 0.5f)},
		{v3(V3F32, 0.0f, 0.0f, 0.0f), v4(V4F32, 1,0,1,1), v2(V2F32, 0.0f, 0.0f)},

	};
  R_Mesh quad_mesh = {0};
	quad_mesh.vertices = v;
	quad_mesh.vertex_count = ArrayCount(v);

  u32 shader_id = ctx.render->api->shader_load(
			str8("./assets/shaders/base_vs.glsl"),
      str8("./assets/shaders/base_fs.glsl"));

  u32 vbo = ctx.render->api->vertex_buffer_create(quad_mesh.vertices, quad_mesh.vertex_count * sizeof(R_VertexData));
  u32 vao = ctx.render->api->vertex_array_create(vbo, quad_mesh.vertices, quad_mesh.vertex_count * sizeof(R_VertexData));

  while (!ctx.is_quit) {
    if (!os_window_poll_events(ctx.window)) {
      os_window_close(ctx.window);
      ctx.is_quit = true;
    }

    application_process_events();

    ctx.render->api->begin(ctx.window->handle, ctx.window->render, v4(V4F32, 0.0f, 0.0f, 1920.0f, 1080.0f));

		// draw quad
		{
			ctx.render->api->shader_bind(shader_id);
			ctx.render->api->vertex_array_bind(vao);
    	ctx.render->api->flush(ctx.window->handle, &quad_mesh);
		}

    ctx.render->api->end(ctx.window->handle);

    os_sleep(1);
  }
}

void application_on_event(OS_Event *event) {
  linked_list_push_front(&ctx.event_list, &event->node);
}

void application_process_events(void) {
  os_input_update(ctx.input);
  LinkedList_Iterator it =
      linked_list_iterator_tail(ctx.event_list, OS_Event, node);
  for (OS_Event *event = linked_list_iterate_prev(&it); event != 0;
       event = linked_list_iterate_prev(&it)) {
    os_input_on_event(ctx.input, event);
    linked_list_remove(&ctx.event_list, &event->node);
    free(event);
  }
}
