#include "tnt_application.h"
#include "tnt_camera.h"
#include "tnt_logger.h"
#include "tnt_math.h"
#include "tnt_os.h"
#include "tnt_render_types.h"
#include "tnt_string.h"
#include "tnt_types.h"

#include <math.h>

global_variable ApplicationState ctx = {0};


void mat4_mult_vec(Vec3F32 *i, Vec3F32 *o, Mat4 m)
{
	o->x = i->x * m[0][0] + i->y * m[1][0] + i->z * m[2][0] + m[3][0];
	o->y = i->x * m[0][1] + i->y * m[1][1] + i->z * m[2][1] + m[3][1];
	o->z = i->x * m[0][2] + i->y * m[1][2] + i->z * m[2][2] + m[3][2];
	float w = i->x * m[0][3] + i->y * m[1][3] + i->z * m[2][3] + m[3][3];
	if (w != 0.0f)
	{
		o->x /= w;
		o->y /= w;
		o->z /= w;
	}
}

void push_entity(OS_Event *event) {
  ASSERT(ctx.events_count > OS_EVENTS_CAPACITY);

  OS_Event *pos = ctx.event_buffer + ctx.events_count;
  memcpy(pos, event, sizeof(OS_Event));
  ctx.events_count += 1;
}

OS_Event *pop_entity() {
  ASSERT(ctx.events_count < 0);

  OS_Event *pos = ctx.event_buffer + ctx.events_count;
  memset(pos, 0, sizeof(OS_Event));
  ctx.events_count -= 1;
  pos = ctx.event_buffer + ctx.events_count;
  return pos;
}

OS_Event *get_entity(u64 index) {
  OS_Event *result = ctx.event_buffer + index;
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

  ctx.event_buffer = push_array_zero(ctx.arena_transient_storage, OS_Event,
                                     OS_EVENTS_CAPACITY);

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
  f64 end_counter = 0.f;

  while (!ctx.is_quit) {
    begin_counter = os_time_now();

    f64 counter_elapsed = (f64)(begin_counter - end_counter);
    f64 ms_per_frame = (f64)(counter_elapsed / perf_count_frequency);
    f64 fps = (f64)(perf_count_frequency / counter_elapsed);

    os_window_poll_events(ctx.window);
    application_process_events();

    if (os_input_button_down(ctx.input, OS_MOUSE_BUTTON_LEFT)) {
      // LOG_DEBUG("[APP] Input: OS_MOUSE_BUTTON_LEFT down");
    }
    if (os_input_button_up(ctx.input, OS_MOUSE_BUTTON_LEFT)) {
      // LOG_DEBUG("[APP] Input: OS_MOUSE_BUTTON_LEFT up");
    }
    if (os_input_key_up(ctx.input, OS_KEYCODE_ESCAPE)) {
      ctx.is_quit = true;
      // LOG_DEBUG("[APP] Input: OS_KEYCODE_ESCAPE");
    }

    local_variable Vec2F32 mouse_pos = v2f32(0.0f, 0.0f);
    os_input_get_mouse_position(ctx.input, &mouse_pos.x, &mouse_pos.y);
    mouse_pos = v2f32((mouse_pos.x / ((f32)ctx.window->width / 2) - 1),
                      -(mouse_pos.y / ((f32)ctx.window->height / 2)) + 1);
    ctx.ui->mouse_pos = mouse_pos; // TODO

    if (ms_per_frame >= period_max) {
      if (ms_per_frame >= 1.f) {
        ms_per_frame = period_max;
      }

      // Input
      local_variable f32 player_speed = 1.0f;
      local_variable Vec2F32 player_pos = v2f32(0.0f, 0.0f);
      {
        if (os_input_key_pressed(ctx.input, OS_KEYCODE_W)) {
          player_pos.y += player_speed * ms_per_frame;
        }
        if (os_input_key_pressed(ctx.input, OS_KEYCODE_S)) {
          player_pos.y -= player_speed * ms_per_frame;
        }
        if (os_input_key_pressed(ctx.input, OS_KEYCODE_A)) {
          player_pos.x -= player_speed * ms_per_frame;
        }
        if (os_input_key_pressed(ctx.input, OS_KEYCODE_D)) {
          player_pos.x += player_speed * ms_per_frame;
        }
      }

      char *title =
          (char *)push_array_zero(ctx.arena_transient_storage, char, 1024);
      sprintf(title, "FPS: %.03ff/s, %.03fms/f | Mouse: %.03ff, %.03ff", fps,
              ms_per_frame, mouse_pos.x, mouse_pos.y);
      os_window_set_title(ctx.window, str8(title));

      // Render
      {
        ctx.render->api->begin(
            ctx.window->handle, ctx.window->render,
            v4f32(0.0f, 0.0f, ctx.window->width, ctx.window->height));

#if 1
        f32 near = 0.1f;
        f32 far = 1000.0f;
        f32 fov = 90.0f;
        f32 aspect_ratio = (f32)ctx.window->height / (f32)ctx.window->width;
        f32 fov_rad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.14159f);

        Mat4 matrix_proj = 
				{
						(f32)ctx.window->width, 0.0f, 0.0f, 0.0f,
						0.0f, (f32)ctx.window->height, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f, 0.0f,
						-1.0f, -1.0f, 0.0f, 1.0f,
				};
        matrix_proj[0][0] = aspect_ratio * fov_rad;
        matrix_proj[1][1] = fov_rad;
        matrix_proj[2][2] = far / (far - near);
        matrix_proj[3][2] = (-far * near) / (far - near);
        matrix_proj[2][3] = 1.0f;
        matrix_proj[3][3] = 0.0f;
				ctx.render->api->shader_bind(ctx.render->debug_shader);
        ctx.render->api->uniform_mat4_set(ctx.render->debug_shader, str8("mpv"),
                                          *matrix_proj);

				Vec3F32 p1 = v3f32(mouse_pos.x, mouse_pos.y, 0.0f);
				Vec3F32 p2 = v3f32(0.0f, 0.0f, 0.0f);
				mat4_mult_vec(&p1, &p2, matrix_proj);
				// mat4_mult_vec(&p2, &p2, matrix_proj);
				// LOG_DEBUG("(%f, %f)", p2.x, p2.y);


        local_variable f32 x = 0;
        debug_draw_rectangle_2d(ctx.render, v2f32(x, 0.0f), v2f32(0.1f, 0.1f),
                                v4f32(1.0f, 0.0f, 1.0f, 1.0f));
        debug_draw_rectangle_2d(ctx.render, v2f32(-x, 0.1f), v2f32(0.1f, 0.1f),
                                v4f32(0.0f, 0.0f, 1.0f, 1.0f));
        debug_draw_rectangle_2d(ctx.render, v2f32(mouse_pos.x, mouse_pos.y),
                                v2f32(0.1f, 0.1f),
                                v4f32(0.0f, 1.0f, 0.0f, 1.0f));
        debug_draw_rectangle_2d(ctx.render, v2f32(player_pos.x, player_pos.y),
                                v2f32(0.1f, 0.1f),
                                v4f32(1.0f, 1.0f, 0.0f, 1.0f));

        debug_draw_line_2d(ctx.render, v2f32(0.0f, 0.0f),
                           v2f32(p2.x, p2.y),
                           v4f32(1.0f, 0.0f, 0.0f, 1.0f));
        debug_draw_line_2d(ctx.render, v2f32(0.0f, 0.0f), v2f32(1.0f, 2.0f),
                           v4f32(0.0f, 1.0f, 0.0f, 1.0f));
        debug_draw_line_2d(ctx.render, v2f32(0.0f, 0.0f), v2f32(1.0f, 3.0f),
                           v4f32(1.0f, 1.0f, 0.0f, 1.0f));

        x += 1.0f * (f32)ms_per_frame;

        if (x >= 1.0f) {
          x = 0.0f;
        }
#endif

        ui_begin(ctx.ui, v2f32(0.0f, 0.0f), 0.01f);
        for (u64 i = 0; i < 8; i += 1) {
          if (ui_button(ctx.ui, ctx.render,
                        v4f32(1.0f / i, 0.0f, 1.0f / i, 1.0f),
                        v2f32(0.1f, 0.1f), i + 1)) {
            LOG_DEBUG("[UI] Button:%lu: click", i);
          }
        }
        ui_end(ctx.ui);

        ctx.render->api->end(ctx.window->handle);
      }
      end_counter = begin_counter;
    }
    os_sleep((u32)ms_per_frame);
  }
}

void application_on_event(OS_Event *event) { push_entity(event); }

void application_process_events(void) {
  OS_Event *event = 0;
  os_input_update(ctx.input);

  for (u64 i = 0; i < ctx.events_count; i += 1) {
    event = get_entity(i);
    switch (event->type) {
    case OS_EVENT_TYPE_APP_QUIT:
      os_window_close(ctx.window);
      ctx.is_quit = true;
      return;
      break;
    case OS_EVENT_TYPE_MOUSE_BUTTON:
      ctx.ui->mouse_button = event->state;
      break;
    }
    os_input_on_event(ctx.input, event);
    pop_entity();
  }
}
