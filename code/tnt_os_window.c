#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

internal OS_Window *os_window_create(const char *title, u32 width, u32 height, u32 xpos, u32 ypos)
{
	local_variable OS_Window *result;
	
	SDL_Init(SDL_INIT_VIDEO);
    result->window = (void *)SDL_CreateWindow(title,
											  xpos, ypos, 
											  width, height, 
											  0);
	return result;
}

internal void os_window_destroy(OS_Window *window)
{
	SDL_DestroyWindow(window->window);
}

internal void os_window_poll_events(OS_Window *window)
{
	local_variable SDL_Event event;
	while (SDL_PollEvent(&event)) 
	{
		window->rect_changed_callback();
		window->event_callback();
		window->input_event_callback();
		window->input_text_callback();
		window->drop_files_callback();
	}
}

internal void os_window_process_events(OS_Window *window)
{
	
}