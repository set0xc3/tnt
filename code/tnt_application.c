#include "tnt_application.h"
#include "tnt_logger.h"
#include "tnt_os.h"

ApplicationState app_state = {0};

void application_init(void) {
  app_state.os_input = malloc(sizeof(OS_Input));

  // create window and add in list
  OS_Window *window = malloc(sizeof(OS_Window));
  os_window_open(window, "Window", 1280, 720, 0, 0);
  linked_list_push_front(&app_state.window_list, &window->node);
  os_window_set_event_callback(window, application_on_event);
}

void application_run(void) {
  while (!app_state.is_quit) {
    if (!linked_list_is_empty(&app_state.window_list)) {
      LinkedList_Iterator it =
          linked_list_iterator_head(app_state.window_list, OS_Window, node);
      for (OS_Window *window = linked_list_iterate_next(&it); window != 0;
           window = linked_list_iterate_next(&it)) {
        if (!os_window_poll_events(window)) {
          os_window_close(window);
          linked_list_remove(&app_state.window_list, &window->node);
          free(window);
        }
      }
    } else {
      app_state.is_quit = true;
    }

    application_process_events();

    if (os_input_button_down(app_state.os_input, OS_MOUSE_BUTTON_LEFT)) {
      LOG_DEBUG("[input] mouse:button1:down");
    }
    if (os_input_button_pressed(app_state.os_input, OS_MOUSE_BUTTON_LEFT)) {
      LOG_DEBUG("[input] mouse:button1:pressed");
    }
    if (os_input_button_up(app_state.os_input, OS_MOUSE_BUTTON_LEFT)) {
      LOG_DEBUG("[input] mouse:button1:up");
    }

    i32 mouse_scroll_y = os_input_get_mouse_scroll_y(app_state.os_input);
    if (mouse_scroll_y != 0) {
      LOG_DEBUG("[input] mouse:scroll:%i", mouse_scroll_y);
    }

    os_sleep(1);
  }
}

void application_on_event(OS_Event *event) {
  linked_list_push_front(&app_state.event_list, &event->node);
}

void application_process_events(void) {
  os_input_update(app_state.os_input);
  LinkedList_Iterator it =
      linked_list_iterator_tail(app_state.event_list, OS_Event, node);
  for (OS_Event *event = linked_list_iterate_prev(&it); event != 0;
       event = linked_list_iterate_prev(&it)) {

    os_input_on_event(app_state.os_input, event);

    linked_list_remove(&app_state.event_list, &event->node);
    free(event);
  }
}
