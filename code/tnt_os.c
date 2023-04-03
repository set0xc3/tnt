#include "tnt_platform.h"

#include "tnt_os_input.c"

#ifdef PLATFORM_LINUX
#include "tnt_os_linux_entry.c"
#include "tnt_os_linux_impl.c"
#include "tnt_os_linux_window.c"
#elif PLATFORM_WIN32
#include "tnt_os_windows_entry.c"
#include "tnt_os_windows_impl.c"
#include "tnt_os_windows_window.c"
#endif

#include <SDL2/SDL.h>

u64 os_time_now(void) { return SDL_GetTicks64(); }
u64 os_time_frequency(void) { return SDL_GetPerformanceFrequency(); }
