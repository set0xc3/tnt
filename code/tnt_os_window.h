#ifndef TNT_OS_WINDOW_H
#define TNT_OS_WINDOW_H

typedef struct OS_Window OS_Window;
struct OS_Window {
	LinkedList_Node node;

	const char* title;
	u32 width, height;
	u32 xpos, ypos;
	
	void* internal_data;
	void(*event_callback)(OS_Event* event);
};

internal b8	  os_window_open(OS_Window* window, const char* title, u32 width, u32 height, u32 xpos, u32 ypos);
internal void os_window_close(OS_Window* window);
internal b8   os_window_poll_events(OS_Window* window);
internal void os_window_set_event_callback(OS_Window* window, void* function);

#endif //TNT_OS_WINDOW_H