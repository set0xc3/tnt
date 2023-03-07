#include <X11/Xlib.h>
#include <X11/Xutil.h>

typedef struct InternalState InternalState;
struct InternalState {
	Window window;
	Display* display;
};

internal b8 os_window_open(OS_Window* window, const char* title, u32 width, u32 height, u32 xpos, u32 ypos) {
	InternalState* in     = malloc(sizeof(InternalState));
	window->title         = title;
	window->width         = width;
	window->height        = height;
	window->xpos          = xpos;
	window->ypos          = ypos;
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
		in->display, 
		RootWindow(in->display, screen_num),
		xpos, ypos, width, height, 0,
		BlackPixel(in->display, screen_num),
		WhitePixel(in->display, screen_num));
	if (in->window == 0) {
		ASSERT(true);
		LOG_ERROR("Failed open window");
		return false;
	}

	XStoreName(in->display, in->window, title);

	u64 input_mask = ExposureMask|ButtonPressMask|KeyPressMask;
    XSelectInput(in->display, in->window, input_mask);

	Atom atom_delete_window = XInternAtom(in->display, "WM_DELETE_WINDOW", 0);
	XSetWMProtocols(in->display, in->window, &atom_delete_window, 1);

	XClearWindow(in->display, in->window);
	XMapWindow(in->display, in->window);

	XFlush(in->display);

	return true;
}

internal void os_window_close(OS_Window* window) {
	InternalState* in = window->internal_data;
	XDestroyWindow(in->display, in->window);
	XCloseDisplay(in->display);
}

internal b8 os_window_poll_events(OS_Window* window) {
	InternalState* in = window->internal_data;
	while (XPending(in->display) > 0) {
		XEvent x_event;
		XNextEvent(in->display, &x_event);

		switch (x_event.type) {
			case ClientMessage: {
				return false;
			} break;
			case Expose: {
			} break;
			case KeyPress: {
				KeySym keysym = XLookupKeysym(&x_event.xkey, 0);
				if (keysym == XK_Escape) 
				{
					return false;
				}
			} break;
			case ButtonPress: {
				OS_Event* event = malloc(sizeof(OS_Event));
				memset(event, 0, sizeof(OS_Event));
				window->event_callback(event);
			} break;
			case PointerMotionMask: {
			} break;
		}
	}
	return true;
}

internal void os_window_set_event_callback(OS_Window* window, void* function) {
	window->event_callback = function;
}