#include "tnt_application.h"
#include "tnt_logger.h"
#include "tnt_os.h"
#include "tnt_render_types.h"
#include "tnt_string.h"
#include "tnt_types.h"
#include "tnt_vector.h"

ApplicationState ctx = {0};

OS_Event *get_entity(u64 index) {
	OS_Event *result = (OS_Event *)ctx.event_list + index;
	return result;
}

void application_init(void) {
	ctx.arena_permanent_storage = arena_create(Megabytes(64));
	ctx.arena_transient_storage = arena_create(Gigabytes(4));
  ctx.input  = push_struct_zero(ctx.arena_permanent_storage, OS_Input);
  ctx.render = push_struct_zero(ctx.arena_permanent_storage, TNT_Render);
  ctx.window = push_struct_zero(ctx.arena_permanent_storage, OS_Window);
	ctx.event_list = (OS_Event *)push_array_zero(ctx.arena_permanent_storage, OS_Event, 1000);

  os_window_open(ctx.window, "Window", 1920, 1080, 0, 0);
  os_window_set_event_callback(ctx.window, application_on_event);

  if (render_load(ctx.render, ctx.window->handle, str8("./librender_opengl"))) {
    LOG_INFO("OpenGL Loaded:");
    LOG_INFO("  Version: %s", ctx.render->api->version);

		debug_render_init(ctx.render);
  }
}

void application_run(void) {
	const f64 fps_max = 60.f;
	const f64 period_max = 1.f / fps_max;
	const f64 perf_count_frequency = os_time_frequency();

	f64 begin_counter = 0.f;
	f64 end_counter   = 0.f;

  while (!ctx.is_quit) {
		begin_counter = os_time_now();

		f64 counter_elapsed = (f64)(begin_counter - end_counter);
		f64 ms_per_frame    = (f64)(counter_elapsed / perf_count_frequency);
		f64 fps             = (f64)(perf_count_frequency / counter_elapsed);

	  os_window_poll_events(ctx.window);

		if (ms_per_frame >= period_max) 
		{
			if (ms_per_frame >= 1.0f) {
				ms_per_frame = period_max;
			}

 			application_process_events();

			// local_variable f64 frame_per_sec = 0;
			// frame_per_sec += ms_per_frame;
			// if (frame_per_sec >= period_max)
			{
				// if (frame_per_sec >= 1.0f) {
				// 	frame_per_sec = period_max;
				// }
 		  	ctx.render->api->begin(ctx.window->handle, ctx.window->render, v4(0.0f, 0.0f, 1920.0f, 1080.0f));

				debug_draw_quad_2d(ctx.render, v2(-1.0f, -1.0f), v2(2.0f, 2.0f), v4(0.6f, 0.6f, 0.6f, 1.0f));

				local_variable f32 x = 0;
				debug_draw_quad_2d(ctx.render, v2(x, 0.0f), v2(0.1f, 0.1f), v4(1.0f, 0.0f, 1.0f, 1.0f));
				debug_draw_quad_2d(ctx.render, v2(-x, 0.1f), v2(0.1f, 0.1f), v4(0.0f, 0.0f, 1.0f, 1.0f));

				debug_draw_line_2d(ctx.render, v2(0.0f, 0.0f), v2(1.0f, 1.0f), v4(1.0f, 0.0f, 0.0f, 1.0f));
				debug_draw_line_2d(ctx.render, v2(0.0f, 0.0f), v2(1.0f, 2.0f), v4(0.0f, 1.0f, 0.0f, 1.0f));
				debug_draw_line_2d(ctx.render, v2(0.0f, 0.0f), v2(1.0f, 3.0f), v4(1.0f, 1.0f, 0.0f, 1.0f));

				x += 1.0f * (f32)ms_per_frame;

				if (x >= 1.0f) {
					x = 0.0f;
				}

    		ctx.render->api->end(ctx.window->handle);

				// LOG_DEBUG("[APP] fps: %.02ff/s, %.03fms/f", 1000.0f/(frame_per_sec * 1000.0f), frame_per_sec);
				// frame_per_sec = 0;
			}
			LOG_DEBUG("[APP] fps: %.02ff/s, %.03fms/f", 1000.0f/(ms_per_frame * 1000.0f), ms_per_frame);
			end_counter = begin_counter;
		}
		os_sleep((u32)ms_per_frame);
  }
}

void application_on_event(OS_Event *event) {
	OS_Event *e = ctx.event_list + ctx.event_index;
	memcpy(e, event, sizeof(OS_Event));
	ctx.event_index += 1;
}

void application_process_events(void) {
	OS_Event *event = 0;
  os_input_update(ctx.input);
  for (u64 i = 0; i < ctx.event_index; i += 1) {
		event = get_entity(i);
		switch (event->type) {
			case OS_EVENT_TYPE_APP_QUIT:
    		os_window_close(ctx.window);
    		ctx.is_quit = true;
				return;
			break;
		}
    os_input_on_event(ctx.input, event);
		memset(event, 0, sizeof(OS_Event));
	  ctx.event_index -= 1;
  }
}
