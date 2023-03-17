#include "tnt_logger.h"
#include "tnt_os.h"
#include "tnt_platform.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>

typedef struct InternalState InternalState;
struct InternalState {
  Window window;
  Display *display;
};

b8 os_window_open(OS_Window *window, const char *title, u32 width, u32 height,
                  u32 xpos, u32 ypos) {
  InternalState *in = malloc(sizeof(InternalState));
  window->title = title;
  window->width = width;
  window->height = height;
  window->xpos = xpos;
  window->ypos = ypos;
  window->internal_data = in;

  i32 screen_num = 0;
  u32 black = 0;
  u32 white = 0;

  in->display = XOpenDisplay(0);
  if (in->display == 0) {
    ASSERT(true);
    LOG_ERROR("Failed open display");
    return false;
  }

  screen_num = DefaultScreen(in->display);

  in->window = XCreateSimpleWindow(
      in->display, RootWindow(in->display, screen_num), xpos, ypos, width,
      height, 0, BlackPixel(in->display, screen_num),
      WhitePixel(in->display, screen_num));
  if (in->window == 0) {
    ASSERT(true);
    LOG_ERROR("Failed open window");
    return false;
  }

  XStoreName(in->display, in->window, title);

  u64 input_mask = ExposureMask | ButtonPressMask | ButtonReleaseMask |
                   KeyPressMask | KeyReleaseMask;
  XSelectInput(in->display, in->window, input_mask);

  Atom atom_delete_window = XInternAtom(in->display, "WM_DELETE_WINDOW", 0);
  XSetWMProtocols(in->display, in->window, &atom_delete_window, 1);

  XClearWindow(in->display, in->window);
  XMapWindow(in->display, in->window);

  XFlush(in->display);

  return true;
}

void os_window_close(OS_Window *window) {
  InternalState *in = window->internal_data;
  XDestroyWindow(in->display, in->window);
  XCloseDisplay(in->display);
}

b8 os_window_poll_events(OS_Window *window) {
  InternalState *in = window->internal_data;
  while (XPending(in->display) > 0) {
    XEvent raw_event;
    XNextEvent(in->display, &raw_event);

		b8 is_down = true;
    OS_Event *event = 0;
    switch (raw_event.type) {
    case ClientMessage: {
      return false;
    } break;
    case Expose: {
    } break;
    case KeyPress: {
      KeySym keysym = XLookupKeysym(&raw_event.xkey, 0);
      if (keysym == XK_Escape) {
        return false;
      }
    } break;
    case ButtonRelease:
      is_down = false;
    case ButtonPress: {
      XButtonEvent *xbutton_event = &raw_event.xbutton;
      switch (xbutton_event->button) {
      case Button1:
        event = malloc(sizeof(OS_Event));
        memset(event, 0, sizeof(OS_Event));
        event->type = OS_EVENT_TYPE_MOUSE_BUTTON;
        event->code = OS_MOUSE_BUTTON_LEFT;
        event->state = is_down;
        break;
      case Button2:
        event = malloc(sizeof(OS_Event));
        memset(event, 0, sizeof(OS_Event));
        event->type = OS_EVENT_TYPE_MOUSE_BUTTON;
        event->code = OS_MOUSE_BUTTON_MIDDLE;
        event->state = is_down;
        break;
      case Button3:
        event = malloc(sizeof(OS_Event));
        memset(event, 0, sizeof(OS_Event));
        event->type = OS_EVENT_TYPE_MOUSE_BUTTON;
        event->code = OS_MOUSE_BUTTON_RIGHT;
        event->state = is_down;
        break;

      case Button4: {
        local_variable u32 frame = 0;
        if (frame == 1) {
          frame = 0;
          break;
        } else {
          event = malloc(sizeof(OS_Event));
          memset(event, 0, sizeof(OS_Event));
          event->type = OS_EVENT_TYPE_MOUSE_SCROLLED;
          event->state = 1;
        }
        frame += 1;
      } break;
      case Button5: {
        local_variable u32 frame = 0;
        if (frame == 1) {
          frame = 0;
          break;
        } else {
          event = malloc(sizeof(OS_Event));
          memset(event, 0, sizeof(OS_Event));
          event->type = OS_EVENT_TYPE_MOUSE_SCROLLED;
          event->state = -1;
        }
        frame += 1;
      } break;
      }

      if (event) {
        LOG_DEBUG("[event] ====================");
        LOG_DEBUG("[event] button:is_down:%u", is_down);
        LOG_DEBUG("[event] button:xstate:%u", xbutton_event->state);
        LOG_DEBUG("[event] button:xcode:%u", xbutton_event->button);
        LOG_DEBUG("[event] button:state:%i", event->state);
        LOG_DEBUG("[event] button:code:%u", event->code);
      }
    } break;
    case PointerMotionMask: {
    } break;
    }
    if (event) {
      window->event_callback(event);
      event = 0;
    }
  }
  return true;
}

void os_window_set_event_callback(OS_Window *window, void *function) {
  window->event_callback = function;
}
