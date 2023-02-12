#ifndef TNT_OS_WINDOW_H
#define TNT_OS_WINDOW_H

typedef struct OS_Window OS_Window;
struct OS_Window
{
	void* window;
	const char *title;
	u32 width, height;
	u32 xpos, ypos;
	
	void (*rect_changed_callback)(void);
	void (*event_callback)(void);
	void (*input_event_callback)(void);
	void (*input_text_callback)(void);
	void (*drop_files_callback)(void);
};

internal OS_Window *os_window_create(const char *title, u32 width, u32 height, u32 xpos, u32 ypos);
internal void os_window_destroy(OS_Window *window);
internal void os_window_poll_events(OS_Window *window);
internal void os_window_process_events(OS_Window *window);

#endif //TNT_OS_WINDOW_H