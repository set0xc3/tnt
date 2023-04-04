#include "tnt_string.h"
#include "tnt_application.h"
#include "tnt_logger.h"
#include "tnt_os.h"

ApplicationState ctx = {0};

void application_init(void) {
  ctx.input = malloc(sizeof(OS_Input));
  ctx.window = malloc(sizeof(OS_Window));
  ctx.render = malloc(sizeof(Render));

  os_window_open(ctx.window, "Window", 1280, 720, 0, 0);
  os_window_set_event_callback(ctx.window, application_on_event);

  if (render_load(ctx.render, str8("./librender_opengl"))) 
  {
		  LOG_INFO("OpenGL Loaded:");
  		LOG_INFO("  Version: %s", ctx.render->api->version);

  		ctx.render->api->init(ctx.window->handle);
	}
}

void application_run(void) {
  while (!ctx.is_quit) {
    if (!os_window_poll_events(ctx.window->handle)) {
      os_window_close(ctx.window->handle);
      ctx.is_quit = true;
    }

    ctx.render->api->begin(ctx.window->handle, ctx.window->render, v4(V4F32, 1.0f, 1.0f, 1.0f, 1.0f));

    application_process_events();

    if (os_input_button_down(ctx.input, OS_MOUSE_BUTTON_LEFT)) {
      LOG_DEBUG("[input] mouse:button1:down");
    }
    if (os_input_button_pressed(ctx.input, OS_MOUSE_BUTTON_LEFT)) {
      LOG_DEBUG("[input] mouse:button1:pressed");
    }
    if (os_input_button_up(ctx.input, OS_MOUSE_BUTTON_LEFT)) {
      LOG_DEBUG("[input] mouse:button1:up");
    }

    i32 mouse_scroll_y = os_input_get_mouse_scroll_y(ctx.input);
    if (mouse_scroll_y != 0) {
      LOG_DEBUG("[input] mouse:scroll:%i", mouse_scroll_y);
    }

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
