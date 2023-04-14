#include "tnt_application.h"
#include "tnt_logger.h"
#include "tnt_os.h"
#include "tnt_render_types.h"
#include "tnt_string.h"
#include "tnt_types.h"
#include "tnt_vector.h"

#define MAX_QUAD_COUNT 1000
#define MAX_VERTEX_COUNT MAX_QUAD_COUNT * 4
#define MAX_INDEX_COUNT MAX_QUAD_COUNT * 6

ApplicationState ctx = {0};

R_VertexData quad_mesh[] = {
  {v3(V3F32, 0.0f, 0.0f, 0.0f), v4(V4F32, 1,0,1,1), v2(V2F32, 0.0f, 0.0f)},
  {v3(V3F32, 0.5f, 0.0f, 0.0f), v4(V4F32, 1,0,1,1), v2(V2F32, 0.5f, 0.0f)},
  {v3(V3F32, 0.5f, 0.5f, 0.0f), v4(V4F32, 1,0,1,1), v2(V2F32, 0.5f, 0.5f)},

  {v3(V3F32, 0.5f, 0.5f, 0.0f), v4(V4F32, 1,0,1,1), v2(V2F32, 0.5f, 0.5f)},
  {v3(V3F32, 0.0f, 0.5f, 0.0f), v4(V4F32, 1,0,1,1), v2(V2F32, 0.0f, 0.5f)},
  {v3(V3F32, 0.0f, 0.0f, 0.0f), v4(V4F32, 1,0,1,1), v2(V2F32, 0.0f, 0.0f)},

};

R_Mesh *quad_mesh_create() {
  R_Mesh *mesh = push_struct_zero(ctx.arena_transient_storage, R_Mesh);
	mesh->vertices = quad_mesh;
	mesh->vertex_count = ArrayCount(quad_mesh);
  return mesh;
}

typedef struct Entity Entity;
struct Entity {
	V3F32 position;
	V3F32 scale;
	R_Mesh *mesh;
};

Entity *entity_create() {
  Entity *result = push_struct_zero(ctx.arena_transient_storage, Entity); 
  result->mesh = quad_mesh_create();
  return result;
}

void entity_mesh_set(Entity *ent, R_Mesh *mesh) {
  ent->mesh = mesh;
}

void application_init(void) {
	ctx.arena_permanent_storage = arena_create(Megabytes(64));
	ctx.arena_transient_storage = arena_create(Gigabytes(4));
  ctx.input  = push_struct_zero(ctx.arena_permanent_storage, OS_Input);
  ctx.render = push_struct_zero(ctx.arena_permanent_storage, TNT_Render);
  ctx.window = push_struct_zero(ctx.arena_permanent_storage, OS_Window);

  os_window_open(ctx.window, "Window", 1920, 1080, 0, 0);
  os_window_set_event_callback(ctx.window, application_on_event);

  if (render_load(ctx.render, str8("./librender_opengl"))) {
    LOG_INFO("OpenGL Loaded:");
    LOG_INFO("  Version: %s", ctx.render->api->version);
    ctx.render->api->init(ctx.window->handle);
  }
}

void application_run(void) {
  Entity *ent = entity_create();

  R_Shader base_shader = ctx.render->api->shader_load(
			str8("./assets/shaders/base_vs.glsl"),
      str8("./assets/shaders/base_fs.glsl"));

  u32 vbo = ctx.render->api->vertex_buffer_create(0, MAX_VERTEX_COUNT);
  u32 vao = ctx.render->api->vertex_array_create(vbo, 0, MAX_VERTEX_COUNT);

  while (!ctx.is_quit) {
    if (!os_window_poll_events(ctx.window)) {
      os_window_close(ctx.window);
      ctx.is_quit = true;
    }

    application_process_events();

    ctx.render->api->begin(ctx.window->handle, ctx.window->render, v4(V4F32, 0.0f, 0.0f, 1920.0f, 1080.0f));

		// draw quad
		{
			ctx.render->api->shader_bind(base_shader);
			ctx.render->api->vertex_array_bind(vao);
      ctx.render->api->vertex_buffer_bind(vbo);
      ctx.render->api->vertex_buffer_update(ent->mesh->vertices, ent->mesh->vertex_count * sizeof(R_VertexData));
    	ctx.render->api->flush(ctx.window->handle, ent->mesh);
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
