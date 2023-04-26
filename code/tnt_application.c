#include "tnt_application.h"
#include "tnt_camera.h"
#include "tnt_entity.h"
#include "tnt_logger.h"
#include "tnt_math.h"
#include "tnt_os.h"
#include "tnt_render_types.h"
#include "tnt_string.h"
#include "tnt_types.h"
#include "tnt_math.h"

#include <math.h>

global_variable ApplicationState ctx = {0};

void event_push(OS_Event *event) {
  ASSERT(ctx.events_count + 1 > OS_EVENTS_CAPACITY);

  OS_Event *pos = ctx.events + ctx.events_count;
  memcpy(pos, event, sizeof(OS_Event));
  ctx.events_count += 1;
}

void event_pop() {
  ASSERT(ctx.events_count == 0);

  OS_Event *pos = ctx.events + ctx.events_count - 1;
  memset(pos, 0, sizeof(OS_Event));
  ctx.events_count -= 1;
}

OS_Event *event_get(u64 index) {
  ASSERT(ctx.events_count == 0);

  OS_Event *result = ctx.events + index;
  return result;
}

void application_init(void) {
  ctx.arena_permanent_storage = arena_create(Megabytes(64));
  ctx.arena_transient_storage = arena_create(Gigabytes(4));
  ctx.input = push_struct_zero(ctx.arena_permanent_storage, OS_Input);
  ctx.render = push_struct_zero(ctx.arena_permanent_storage, TNT_Render);
  ctx.window = push_struct_zero(ctx.arena_permanent_storage, OS_Window);
  ctx.ui = push_struct_zero(ctx.arena_permanent_storage, UI_State);
  ctx.camera = push_struct_zero(ctx.arena_permanent_storage, Camera);

  ctx.events = push_array_zero(ctx.arena_transient_storage, OS_Event,
                               OS_EVENTS_CAPACITY);

  os_window_open(ctx.window, "Window", 1920, 1080, 0, 0);
  os_window_set_event_callback(ctx.window, application_on_event);

  if (render_load(ctx.render, ctx.window->handle, str8("./librender_opengl"))) {
    LOG_INFO("OpenGL Loaded:");
    LOG_INFO("  Version: %s", ctx.render->api->version);

    render_init(ctx.render);
  }
}

void application_run(void) {
  const f64 fps_max = 60.f;
  const f64 period_max = 1.f / fps_max;
  const f64 perf_count_frequency = os_time_frequency();

  f64 begin_counter = 0.f;
  f64 end_counter = 0.f;

  Entity *ent1 = entity_push(v3(0.0f, 0.0f, 0.0f), v3(1.0f, 1.0f, 1.0f));

  LOG_DEBUG("(%f, %f)", ent1->pos.x, ent1->pos.y);

  while (!ctx.is_quit) {
    begin_counter = os_time_now();

    f64 counter_elapsed = (f64)(begin_counter - end_counter);
    f64 ms_per_frame = (f64)(counter_elapsed / perf_count_frequency);
    f64 fps = (f64)(perf_count_frequency / counter_elapsed);

    os_window_poll_events(ctx.window);
    application_process_events();

    if (os_input_button_down(ctx.input, OS_MOUSE_BUTTON_LEFT)) {
      LOG_DEBUG("[APP] Input: OS_MOUSE_BUTTON_LEFT down");
    }
    if (os_input_button_up(ctx.input, OS_MOUSE_BUTTON_LEFT)) {
      LOG_DEBUG("[APP] Input: OS_MOUSE_BUTTON_LEFT up");
    }
    if (os_input_key_up(ctx.input, OS_KEYCODE_ESCAPE)) {
      ctx.is_quit = true;
      LOG_DEBUG("[APP] Input: OS_KEYCODE_ESCAPE");
    }

    local_variable Vec2 mouse_pos = {0};
    os_input_get_mouse_position(ctx.input, &mouse_pos.x, &mouse_pos.y);

		// mouse_pos.x = 1.0 + 2.0 * (f32)mouse_pos.x / (f32)ctx.window->width; 
		// mouse_pos.y = 1.0 - 2.0 * (f32)mouse_pos.y / (f32)ctx.window->height;

		// mouse_pos.x = (f32)mouse_pos.x / ((f32)ctx.window->width/2) - 1.0f; 
		// mouse_pos.y = -1 * ((f32)mouse_pos.y / ((f32)ctx.window->height/2) - 1.0f);
		
		// mouse_pos.x = ((f32)mouse_pos.x / (f32)ctx.window->width) * 2.0f - 1.0f;
		// mouse_pos.y = -((f32)mouse_pos.y / (f32)ctx.window->height) * 2.0f + 1.0f;

		// mouse_pos.x = (f32)(mouse_pos.x * (f32)ctx.window->width  / (f32)ctx.window->width);
		// mouse_pos.y = (f32)(mouse_pos.y * (f32)ctx.window->height  / (f32)ctx.window->height);

    // ctx.ui->mouse_pos = mouse_pos; // TODO

    if (ms_per_frame >= period_max) {
      if (ms_per_frame >= 1.f) {
        ms_per_frame = period_max;
      }

      // Input
      local_variable f32 player_speed = 1.0f;
      {
        if (os_input_key_pressed(ctx.input, OS_KEYCODE_W)) {
          ent1->pos.y += player_speed * ms_per_frame;
        }
        if (os_input_key_pressed(ctx.input, OS_KEYCODE_S)) {
          ent1->pos.y -= player_speed * ms_per_frame;
        }
        if (os_input_key_pressed(ctx.input, OS_KEYCODE_A)) {
          ent1->pos.x -= player_speed * ms_per_frame;
        }
        if (os_input_key_pressed(ctx.input, OS_KEYCODE_D)) {
          ent1->pos.x += player_speed * ms_per_frame;
        }
      }

      // Render
      {
				  f32 near = 0.1f;
				  f32 far = 1000.0f;
				  f32 fov = 45.0f;
				  f32 aspect_ratio = (f32)ctx.window->height / (f32)ctx.window->width;
				  Vec3 camera_pos = v3(-ent1->pos.x, -ent1->pos.y, 0.0f);
				  
				  // p*v*m
				  Mat4 projection = mat4_perspective(fov, aspect_ratio, near, far); 
				  Mat4 view = mat4_translate(mat4_identity(), v3(0.0f, 0.0f, 100.0f)); 
				  Mat4 model = mat4_translate(mat4_identity(), camera_pos); 
				  // Mat4 translate = mat4_translate(mat4_identity(), v3(-1.0f, -1.0f, 0.0f)); 
				  // projection = mat4_mul(&projection, &translate); 
				  // mat4_print(&mpv);
				  ctx.render->api->shader_bind(ctx.render->debug_shader);
				  ctx.render->api->uniform_mat4_set(ctx.render->debug_shader, str8("projection"), *projection.m);
				  ctx.render->api->uniform_mat4_set(ctx.render->debug_shader, str8("view"), *view.m);
				  ctx.render->api->uniform_mat4_set(ctx.render->debug_shader, str8("model"), *model.m);

				  ctx.render->api->shader_bind(ctx.render->default_shader);
				  ctx.render->api->uniform_mat4_set(ctx.render->default_shader, str8("projection"), *projection.m);
				  ctx.render->api->uniform_mat4_set(ctx.render->default_shader, str8("view"), *view.m);
				  ctx.render->api->uniform_mat4_set(ctx.render->default_shader, str8("model"), *model.m);

					// Vec3 screen_pos = mat4_world_to_screen(&view, v3(mouse_pos.x, mouse_pos.y, 1.0f));
					// mouse_pos = v2(screen_pos.x, screen_pos.y);

			    char *title =
          (char *)push_array_zero(ctx.arena_transient_storage, char, 4096);
      		sprintf(title, "FPS: %.03ff/s, %.03fms/f | Mouse: %.03ff, %.03ff", fps,
              ms_per_frame, mouse_pos.x, mouse_pos.y);
      		os_window_set_title(ctx.window, str8(title));


        ctx.render->api->begin(ctx.window->handle, ctx.window->render, v4(0.0f, 0.0f, ctx.window->width, ctx.window->height));

#if 1	
				Vec3 cube_positions[] = 
				{
        	v3( 0.0f,  0.0f,  0.0f),
        	v3( 2.0f,  5.0f, -15.0f),
        	v3(-1.5f, -2.2f, -2.5f),
        	v3(-3.8f, -2.0f, -12.3f),
        	v3( 2.4f, -0.4f, -3.5f),
        	v3(-1.7f,  3.0f, -7.5f),
        	v3( 1.3f, -2.0f, -2.5f),
        	v3( 1.5f,  2.0f, -2.5f),
        	v3( 1.5f,  0.2f, -1.5f),
        	v3(-1.3f,  1.0f, -1.5f)
    		};
				for (u32 i = 0; i < 10; i++)
				{
					Vec3 pos = v3(0.0f, 0.0f, 0.0f);
					Mat4 model = mat4_translate(mat4_identity(), cube_positions[i]); 
				  ctx.render->api->shader_bind(ctx.render->default_shader);
				  ctx.render->api->uniform_mat4_set(ctx.render->default_shader, str8("model"), *model.m);
        	draw_cube(ctx.render, v3(0.0f, 0.0f, 0.0f), v2(1.0f, 1.0f), v4(1.0f, 0.0f, 1.0f, 1.0f));
				}

        local_variable f32 x = 0;
        x += 10.0f * sin((f32)ms_per_frame * 0.1f);
        draw_rectangle(ctx.render, v2(x, 0.0f), v2(0.1f, 0.1f),
                       v4(1.0f, 0.0f, 1.0f, 1.0f));
        // debug_draw_rectangle_2d(ctx.render, v2f32(-x, 0.1f), v2f32(0.1f,
        // 0.1f),
        //                         v4f32(0.0f, 0.0f, 1.0f, 1.0f));
        // draw_rectangle(ctx.render, v2(mouse_pos.x, mouse_pos.y), v2(0.1f, 0.1f),
        //                v4(0.0f, 1.0f, 0.0f, 1.0f));
        draw_rectangle(ctx.render, v2(ent1->pos.x, ent1->pos.y), v2(0.1f, 0.1f),
                       v4(1.0f, 1.0f, 0.0f, 1.0f));

        // debug_draw_line_2d(ctx.render, v2f32(0.0f, 0.0f),
        //                    v2f32(p2.x, p2.y),
        //                    v4f32(1.0f, 0.0f, 0.0f, 1.0f));
        // debug_draw_line_2d(ctx.render, v2f32(0.0f, 0.0f), v2f32(1.0f, 2.0f),
        //                    v4f32(0.0f, 1.0f, 0.0f, 1.0f));
        // debug_draw_line_2d(ctx.render, v2f32(0.0f, 0.0f), v2f32(1.0f, 3.0f),
        //                    v4f32(1.0f, 1.0f, 0.0f, 1.0f));

        if (x >= 1.0f) {
          x = 0.0f;
        }
#endif
        //
        // ui_begin(ctx.ui, v2(0.1f, 0.1f), 0.01f);
        // if (ui_button(ctx.ui, ctx.render, v4(1.0f, 0.0f, 1.0f, 1.0f),
        //               v2(0.1f, 0.1f), 1)) {
        //   LOG_DEBUG("[UI] Button:%lu: click", 1);
        // }
        // ui_end(ctx.ui);

        ctx.render->api->end(ctx.window->handle);
      }
      end_counter = begin_counter;
    }
    os_sleep((u32)ms_per_frame);
  }
}

void application_on_event(OS_Event *event) { event_push(event); }

void application_process_events(void) {
  OS_Event *event = 0;
  os_input_update(ctx.input);

  for (u64 i = 0; i < ctx.events_count; i += 1) {
    event = event_get(i);
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
    event_pop();
  }
}
