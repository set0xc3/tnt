#include "tnt_logger.h"
#include "tnt_os.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_video.h>

b8 os_window_open(OS_Window *window, const char *title, u32 width, u32 height,
				  u32 xpos, u32 ypos)
{
	u32 window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
	// #if RENDER_OPENGL
	window_flags |= SDL_WINDOW_OPENGL;
	// #endif

	if (SDL_Init(SDL_INIT_VIDEO < 0))
	{
		LOG_ERROR("[SDL] Failed init sdl");
		return false;
	}

	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");
	SDL_SetHintWithPriority(SDL_HINT_RENDER_VSYNC, "0", SDL_HINT_OVERRIDE);

	// #if RENDER_OPENGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
	SDL_GL_SetSwapInterval(0);
	// #endif

	window->handle = SDL_CreateWindow("My Window", xpos, ypos, width, height, window_flags);
	if (!window->handle)
	{
		LOG_ERROR("[SDL] Failed create window");
		return false;
	}

	// SDL_SetWindowFullscreen(window->handle, SDL_WINDOW_FULLSCREEN_DESKTOP);

	window->title = title;
	window->render = SDL_GL_CreateContext(window->handle);
	window->xpos = xpos;
	window->ypos = ypos;
	window->width = width;
	window->height = height;

	return true;
}

void os_window_close(OS_Window *window)
{
	SDL_DestroyWindow(window->handle);
	SDL_Quit();
}

void os_window_poll_events(OS_Window *window)
{
	OS_Event os_event = {0};
	SDL_Event sdl_event = {0};
	SDL_PollEvent(&sdl_event);

	switch (sdl_event.type)
	{
	case SDL_WINDOWEVENT:
		switch (sdl_event.window.event)
		{
		case SDL_WINDOWEVENT_RESIZED:
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			os_event.kind = OS_EVENT_KIND_WINDOW_RESIZED;
			os_event.window_width = sdl_event.window.data1;
			os_event.window_height = sdl_event.window.data2;
			break;
		}
		break;
	case SDL_QUIT:
		os_event.kind = OS_EVENT_KIND_APP_QUIT;
		break;
	case SDL_MOUSEMOTION:
		os_event.kind = OS_EVENT_KIND_MOUSE_MOTION;
		os_event.mouse_x = sdl_event.motion.x;
		os_event.mouse_y = sdl_event.motion.y;
		break;
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
	{
		os_event.kind = OS_EVENT_KIND_MOUSE_BUTTON;
		os_event.state = sdl_event.button.state == SDL_PRESSED ? true : false;
		switch (sdl_event.button.button)
		{
		case SDL_BUTTON_LEFT:
			os_event.code = OS_MOUSE_BUTTON_LEFT;
			break;
		case SDL_BUTTON_MIDDLE:
			os_event.code = OS_MOUSE_BUTTON_MIDDLE;
			break;
		case SDL_BUTTON_RIGHT:
			os_event.code = OS_MOUSE_BUTTON_RIGHT;
			break;
		}
	}
	break;
	case SDL_KEYDOWN:
	case SDL_KEYUP:
	{
		os_event.kind = OS_EVENT_KIND_KEY_CODE;
		os_event.state = sdl_event.key.state == SDL_PRESSED ? true : false;
		switch (sdl_event.key.keysym.sym)
		{
		case SDLK_w:
			os_event.code = OS_KEYCODE_W;
			break;
		case SDLK_s:
			os_event.code = OS_KEYCODE_S;
			break;
		case SDLK_a:
			os_event.code = OS_KEYCODE_A;
			break;
		case SDLK_d:
			os_event.code = OS_KEYCODE_D;
			break;
		case SDLK_q:
			os_event.code = OS_KEYCODE_Q;
			break;
		case SDLK_e:
			os_event.code = OS_KEYCODE_E;
			break;
		case SDLK_ESCAPE:
			os_event.code = OS_KEYCODE_ESCAPE;
			break;
		}
	}
	break;
	}

	if (os_event.kind != OS_EVENT_KIND_NONE)
	{
		window->event_callback(&os_event);
		memset(&os_event, 0, sizeof(OS_Event));
	}
}

void os_window_set_event_callback(OS_Window *window, void *function)
{
	window->event_callback = function;
}

void os_window_set_title(OS_Window *window, String8 title)
{
	SDL_SetWindowTitle((SDL_Window *)window->handle, str8_to_char(title));
}
