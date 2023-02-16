#ifndef TNT_OS_WINDOW_H
#define TNT_OS_WINDOW_H

typedef struct OS_Window OS_Window;
struct OS_Window
{
	const char *title;
	u32 width, height;
	u32 xpos, ypos;
	
	void *internal_data;
};

internal b8 os_window_create(OS_Window *ctx, const char *title, u32 width, u32 height, u32 xpos, u32 ypos);
internal void os_window_destroy(OS_Window *window);
internal b8 os_window_poll_events(OS_Window *window);
internal void os_window_process_events(OS_Window *window);

#endif //TNT_OS_WINDOW_H