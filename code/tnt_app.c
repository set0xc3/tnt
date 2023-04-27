#include "tnt_app.h"
#include "tnt_camera.h"
#include "tnt_entity.h"
#include "tnt_logger.h"
#include "tnt_math.h"
#include "tnt_os.h"
#include "tnt_render_types.h"
#include "tnt_scene.h"
#include "tnt_string.h"
#include "tnt_types.h"
#include "tnt_math.h"

#include <math.h>

global_variable AppState ctx;

void app_init(void) {
  ctx.arena_permanent_storage = arena_create(Megabytes(64));
  ctx.arena_transient_storage = arena_create(Gigabytes(4));
  ctx.input = push_struct_zero(ctx.arena_permanent_storage, OS_Input);
  ctx.render = push_struct_zero(ctx.arena_permanent_storage, TNT_Render);
  ctx.window = push_struct_zero(ctx.arena_permanent_storage, OS_Window);
  ctx.ui = push_struct_zero(ctx.arena_permanent_storage, UI_State);
  ctx.scene = push_struct_zero(ctx.arena_transient_storage, Scene);
  
	ctx.events = push_array_zero(ctx.arena_transient_storage, OS_Event, OS_EVENTS_CAPACITY);

  os_window_open(ctx.window, "Window", 1920, 1080, 0, 0);
  os_window_set_event_callback(ctx.window, app_on_event);

  if (render_load(ctx.render, ctx.window->handle, str8("./librender_opengl"))) {
    LOG_INFO("OpenGL Loaded:");
    LOG_INFO("  Version: %s", ctx.render->api->version);

    render_init(ctx.render);
  }

	scene_init(ctx.scene, ctx.arena_transient_storage);
}

void app_run(void) {
  const f64 fps_max = 60.f;
  const f64 period_max = 1.f / fps_max;
  const f64 perf_count_frequency = os_time_frequency();

  f64 begin_counter = 0.f;
	f64 end_counter = 0.f;

  while (!ctx.is_quit) {
    begin_counter = os_time_now();

    f64 counter_elapsed = (f64)(begin_counter - end_counter);
    f64 ms_per_frame = (f64)(counter_elapsed / perf_count_frequency);
    f64 fps = (f64)(perf_count_frequency / counter_elapsed);

    os_window_poll_events(ctx.window);
    app_process_events();

    if (ms_per_frame >= period_max) 
		{
      if (ms_per_frame >= 1.f) {
        ms_per_frame = period_max;
      }

			scene_update(ctx.scene, ctx.input, ms_per_frame);

			render_begin(ctx.window, ctx.render, scene_get_camera(ctx.scene), ctx.render->default_shader);

			for (u32 index = 0; 
					 index < scene_get_entites_count(ctx.scene); 
					 index += 1)
			{
				Entity *ent = scene_get_entity(ctx.scene, index);
				Mat4 model = mat4_translate(ent->position);
				ctx.render->api->uniform_mat4_set(ctx.render->default_shader, str8("model"), *model.m);
				render_flush(ctx.render, ent->mesh);
			}
			render_end(ctx.render, ctx.window->handle);

      end_counter = begin_counter;
    }

    os_sleep((u32)ms_per_frame);
  }
}

void app_on_event(OS_Event *event) { app_push_event(event); }

void app_process_events(void) {
  OS_Event *event = 0;
  os_input_update(ctx.input);

  for (u64 i = 0; i < ctx.events_count; i += 1) {
    event = app_get_event(i);
    switch (event->kind) {
    case OS_EVENT_KIND_APP_QUIT:
      os_window_close(ctx.window);
      ctx.is_quit = true;
      return;
      break;
    case OS_EVENT_KIND_MOUSE_BUTTON:
      ctx.ui->mouse_button = event->state;
      break;
    case OS_EVENT_KIND_WINDOW_RESIZED:
				ctx.window->width = event->window_width;
				ctx.window->height = event->window_height;
      break;
    }
    os_input_on_event(ctx.input, event);
    app_pop_event();
  }
}

void app_push_event(OS_Event *event) 
{
  ASSERT(ctx.events_count + 1 > OS_EVENTS_CAPACITY);

  OS_Event *pos = ctx.events + ctx.events_count;
  memcpy(pos, event, sizeof(OS_Event));
  ctx.events_count += 1;
}

void app_pop_event() 
{
  ASSERT(ctx.events_count == 0);

  OS_Event *pos = ctx.events + ctx.events_count - 1;
  memset(pos, 0, sizeof(OS_Event));
  ctx.events_count -= 1;
}

OS_Event *app_get_event(u64 index) 
{
  ASSERT(ctx.events_count == 0);

  OS_Event *result = ctx.events + index;
  return result;
}
