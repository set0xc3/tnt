#include "tnt_app.h"

#include <math.h>

#include "tnt_base_types.h"
#include "tnt_camera.h"
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

      camera_on_resize(&camera, ctx.window->width, ctx.window->height);
      camera_update(&camera, ctx.input, ms_per_frame);

      render_begin(ctx.render, ctx.window);

      f32 half_height = ctx.window->height / 2.0f;
      f32 half_width = ctx.window->width / 2.0f;

      Vec2 mouse_pos = os_input_get_mouse_position(ctx.input);
      mouse_pos.x = mouse_pos.x - half_width;
      mouse_pos.y = -mouse_pos.y + half_height;
#if 1
      {
        Mat4 projection_matrix = camera_get_perspective_matrix(&camera);
        Mat4 view_matrix = camera_get_view_matrix(&camera);

        Vec3 model_pos = v3(0.0f, 0.0f, 0.0f);
        Mat4 model_matrix = m_identity_m4(1.0f);
        model_matrix = m_mul_m4(
            m_translate(model_pos),
            m_rotate_rh(time * m_to_radiansf(50.0f), v3(0.5f, 1.0f, 0.0f)));

        gl_shader_bind(ctx.render->shader_3d);
        gl_uniform_mat4_set(ctx.render->shader_3d, str8("projection"),
                            *projection_matrix.elements);
        gl_uniform_mat4_set(ctx.render->shader_3d, str8("view"),
                            *view_matrix.elements);
        gl_uniform_mat4_set(ctx.render->shader_3d, str8("model"),
                            *model_matrix.elements);

        gl_vertex_array_bind(model_quad.vao);
        gl_flush(DRAWING_MODE_TRIANGLES, model_quad.meshes->vertices_count,
                 model_quad.meshes->indices_count);

        gl_vertex_array_bind(model_cube.vao);
        gl_flush(DRAWING_MODE_TRIANGLES, model_cube.meshes->vertices_count,
                 model_cube.meshes->indices_count);
      }
#endif

#if 1
      {
        Mat4 ortho_matrix = camera_get_orthographic_matrix(&camera);
        Mat4 view_matrix = m_identity_m4(1.0f);
        Mat4 model_matrix = m_identity_m4(1.0f);

        render_draw_rect(ctx.render, v4(-200.0f, 0.0f, 100.0f, 100.0f),
                         COLOR_PINK);
        render_draw_rect(ctx.render,
                         v4(mouse_pos.x, mouse_pos.y, 100.0f, 100.0f),
                         COLOR_PINK);

        gl_shader_bind(ctx.render->shader_2d);
        gl_uniform_mat4_set(ctx.render->shader_2d, str8("projection"),
                            *ortho_matrix.elements);
        gl_uniform_mat4_set(ctx.render->shader_2d, str8("view"),
                            *view_matrix.elements);

        gl_uniform_mat4_set(ctx.render->shader_2d, str8("model"),
                            *model_matrix.elements);
        gl_vertex_buffer_bind(ctx.render->quad_vbo);
        gl_vertex_buffer_update(ctx.render->quad_buffer,
                                sizeof(ctx.render->quad_buffer));
        gl_vertex_array_bind(ctx.render->quad_vao);
      }
      gl_flush(DRAWING_MODE_TRIANGLES, ctx.render->quad_buffer_idx, 0);
#endif

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
