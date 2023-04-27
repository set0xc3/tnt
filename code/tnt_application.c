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

global_variable ApplicationState ctx;

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
  ctx.events = push_array_zero(ctx.arena_transient_storage, OS_Event, OS_EVENTS_CAPACITY);

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

  f32 aspect_ratio = (f32)ctx.window->height / (f32)ctx.window->width;
	
	camera_create(ctx.camera, 45.0f, aspect_ratio, 0.1f, 1000.0f);
  Entity *ent1 = entity_push(V3_ZERO, V3_ONE);

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

    local_variable Vec2 mouse_pos;
    os_input_get_mouse_position(ctx.input, &mouse_pos.x, &mouse_pos.y);

    if (ms_per_frame >= period_max) 
		{
      if (ms_per_frame >= 1.f) {
        ms_per_frame = period_max;
      }

      // Input
      local_variable f32 player_speed = 1.0f;
      {
        if (os_input_key_pressed(ctx.input, OS_KEYCODE_W)) {
          ctx.camera->position.z += player_speed * ms_per_frame;
        }
        if (os_input_key_pressed(ctx.input, OS_KEYCODE_S)) {
          ctx.camera->position.z -= player_speed * ms_per_frame;
        }
        if (os_input_key_pressed(ctx.input, OS_KEYCODE_A)) {
          ctx.camera->position.x += player_speed * ms_per_frame;
        }
        if (os_input_key_pressed(ctx.input, OS_KEYCODE_D)) {
          ctx.camera->position.x -= player_speed * ms_per_frame;
        }
        if (os_input_key_pressed(ctx.input, OS_KEYCODE_Q)) {
          ctx.camera->position.y += player_speed * ms_per_frame;
        }
        if (os_input_key_pressed(ctx.input, OS_KEYCODE_E)) {
          ctx.camera->position.y -= player_speed * ms_per_frame;
        }
      }

      // Render
      {			  
				camera_update(ctx.camera);
				render_begin(ctx.window, ctx.render, ctx.camera, ctx.render->default_shader);
				
				// Vec3 world_coord = screen_to_world(mouse_pos, projection, view, ctx.window->width, ctx.window->height);
				// mouse_pos.x = world_coord.x;
				// mouse_pos.y = world_coord.y;

		    char *title =
        (char *)push_array_zero(ctx.arena_transient_storage, char, 4096);
    		sprintf(title, "FPS: %.03ff/s, %.03fms/f | Mouse: %.03ff, %.03ff", fps,
            ms_per_frame, mouse_pos.x, mouse_pos.y);
    		os_window_set_title(ctx.window, str8(title));


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
				for (u32 i = 0; i < ArrayCount(cube_positions); i++)
				{
					Vec3 pos = V3_ZERO;
					Mat4 model = mat4_translate(cube_positions[i]); 
				  ctx.render->api->shader_bind(ctx.render->default_shader);
				  ctx.render->api->uniform_mat4_set(ctx.render->default_shader, str8("model"), *model.m);
        	draw_cube(ctx.render, V3_ZERO, V2_ONE, COLOR_GREEN_DARK);
				}
				{
					static float time = 0; // current time in seconds
					float speed = 1.5f; // rotation speed in radians per second
					float angle = sin(time * speed * 2.0f * M_PI); // current rotation angle in radians
					Vec3 axis = v3(0.0f, 1.0f, 0.0f);
					Vec3 pos = V3_ZERO;
					Mat4 rotation_matrix = mat4_rotate(time * speed * 2.0f * M_PI, axis);
					Mat4 scale_matrix = mat4_scale(v3(0.1f, 0.1f, 0.1f));

					Mat4 model = mat4_translate(pos);
					model = mat4_mul_mat4(rotation_matrix, model); 
					model = mat4_mul_mat4(scale_matrix, model); 

				  ctx.render->api->shader_bind(ctx.render->default_shader);
				  ctx.render->api->uniform_mat4_set(ctx.render->default_shader, str8("model"), *model.m);
        	draw_cube(ctx.render, V3_ZERO, V2_ZERO, COLOR_BLUE_DARK);

					time += 0.1f * ms_per_frame;
				}

				{
					Vec3 pos = v3(0.0f, 0.0f, 0.0f);
					Mat4 model = mat4_translate(pos);

				  ctx.render->api->shader_bind(ctx.render->debug_shader);
				  ctx.render->api->uniform_mat4_set(ctx.render->debug_shader, str8("model"), *model.m);
        	draw_rectangle(ctx.render, V2_ZERO, V2_ZERO, COLOR_BLUE_DARK);
				}

      }
			render_end(ctx.render, ctx.window->handle);
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
				camera_on_resize(ctx.camera, v4(0.0f, 0.0f, event->window_width, event->window_height));
      break;
    }
    os_input_on_event(ctx.input, event);
    event_pop();
  }
}

