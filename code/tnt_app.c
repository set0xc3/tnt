#include "tnt_app.h"

#include <math.h>

#include "tnt_base_types.h"
#include "tnt_camera.h"
#include "tnt_entity.h"
#include "tnt_math.h"
#include "tnt_os.h"
#include "tnt_render_internal.c"
#include "tnt_render_types.h"
#include "tnt_scene.h"

global_variable AppState ctx;

void app_init(void) {
  ctx.arena_permanent_storage = arena_create(Megabytes(64));
  ctx.arena_transient_storage = arena_create(Gigabytes(4));
  ctx.input = push_struct_zero(ctx.arena_permanent_storage, OS_Input);
  ctx.render = push_struct_zero(ctx.arena_permanent_storage, RenderState);
  ctx.window = push_struct_zero(ctx.arena_permanent_storage, OS_Window);
  ctx.ui = push_struct_zero(ctx.arena_permanent_storage, UI_State);
  ctx.scene = push_struct_zero(ctx.arena_transient_storage, Scene);

  ctx.events = push_array_zero(ctx.arena_transient_storage, OS_Event,
                               OS_EVENTS_CAPACITY);

  os_window_open(ctx.window, "Window", 1920, 1080, 0, 0);
  os_window_set_event_callback(ctx.window, app_on_event);

  render_init(ctx.render, ctx.window);

  scene_init(ctx.scene, ctx.arena_transient_storage);
}

void app_run(void) {
  const f64 fps_max = 60.0;
  const f64 period_max = 1.0 / fps_max;
  const f64 perf_count_frequency = os_time_frequency();

  f64 time = 0.0;

  f64 begin_counter = 0.0;
  f64 end_counter = 0.0;

  R_Model model_quad = {0};
  render_create_model(ctx.render, MODEL_STATIC_QUAD, &model_quad);

  R_Model model_cube = {0};
  render_create_model(ctx.render, MODEL_STATIC_CUBE, &model_cube);

  Camera camera = {0};
  camera_create(&camera, 45.0f, 0.5625f, 0.1f, 1000.0f);

  while (!ctx.is_quit) {
    begin_counter = os_time_now();

    f64 counter_elapsed = (f64)(begin_counter - end_counter);
    f64 ms_per_frame = (f64)(counter_elapsed / perf_count_frequency);
    f64 fps = (f64)(perf_count_frequency / counter_elapsed);

    os_window_poll_events(ctx.window);
    app_process_events();

    if (ms_per_frame >= period_max) {
      if (ms_per_frame >= 1.f) {
        ms_per_frame = period_max;
      }

      camera_on_resize(&camera,
                       v4(0, 0, ctx.window->width, ctx.window->height));
      camera_update(&camera, ctx.input, ms_per_frame);

      render_begin(ctx.render, ctx.window);

      gl_shader_bind(ctx.render->shader_3d);

      Mat4 projection_matrix = camera_get_projection_matrix(&camera);
      Mat4 view_matrix = camera_get_view_matrix(&camera);
      Mat4 model_matrix = mat4_identity();
      model_matrix =
          mat4_rotate(time * to_radiansf(50.0f), v3(0.5f, 1.0f, 0.0f));

      gl_uniform_mat4_set(ctx.render->shader_3d, str8("projection"),
                          *projection_matrix.e);
      gl_uniform_mat4_set(ctx.render->shader_3d, str8("view"), *view_matrix.e);
      gl_uniform_mat4_set(ctx.render->shader_3d, str8("model"),
                          *model_matrix.e);

      gl_flush(DRAWING_MODE_TRIANGLES, &model_quad);
      gl_flush(DRAWING_MODE_TRIANGLES, &model_cube);

      render_end(ctx.render, ctx.window);

      end_counter = begin_counter;
      time += ms_per_frame;
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
    scene_on_resize(ctx.scene, v4(ctx.window->xpos, ctx.window->ypos,
                                  ctx.window->width, ctx.window->height));
    app_pop_event();
  }
}

void app_push_event(OS_Event *event) {
  ASSERT(ctx.events_count + 1 > OS_EVENTS_CAPACITY);

  OS_Event *pos = ctx.events + ctx.events_count;
  memcpy(pos, event, sizeof(OS_Event));
  ctx.events_count += 1;
}

void app_pop_event(void) {
  ASSERT(ctx.events_count == 0);

  OS_Event *pos = ctx.events + ctx.events_count - 1;
  memset(pos, 0, sizeof(OS_Event));
  ctx.events_count -= 1;
}

OS_Event *app_get_event(u64 index) {
  ASSERT(ctx.events_count == 0);

  OS_Event *result = ctx.events + index;
  return result;
}
