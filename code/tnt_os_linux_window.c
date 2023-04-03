#include "tnt_logger.h"
#include "tnt_os.h"

#include <SDL2/SDL.h>

b8 os_window_open(OS_Window *window, const char *title, u32 width, u32 height,
                  u32 xpos, u32 ypos) {
  u32 window_flags = SDL_WINDOW_SHOWN;
  // #if RENDER_OPENGL
  window_flags |= SDL_WINDOW_OPENGL;
  // #endif

  SDL_Window *sdl_window = 0;

  if (SDL_Init(SDL_INIT_VIDEO < 0)) {
    LOG_ERROR("[SDL] Failed init sdl");
    return false;
  }

  // #if RENDER_OPENGL
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  SDL_GL_SetSwapInterval(1);
  // #endif

  sdl_window =
      SDL_CreateWindow("My Window", xpos, ypos, width, height, window_flags);
  if (!sdl_window) {
    LOG_ERROR("[SDL] Failed create window");
    return false;
  }

  return true;
}

void os_window_close(OS_Window *window) {
  SDL_DestroyWindow(window->handle);
  SDL_Quit();
}

b8 os_window_poll_events(OS_Window *window) {
  SDL_Event sdl_event;
  SDL_PollEvent(&sdl_event);

  switch (sdl_event.type) {
  case SDL_QUIT: {
    return false;
  } break;
  }

  return true;
}

void os_window_set_event_callback(OS_Window *window, void *function) {
  window->event_callback = function;
}
