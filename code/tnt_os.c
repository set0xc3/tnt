#include <stdio.h>
#include "tnt_platform.h"

#include "tnt_os_input.c"
#include "tnt_os_window.c"

#ifdef PLATFORM_LINUX
#include "tnt_os_linux_entry.c"
#include "tnt_os_linux_impl.c"
#elif PLATFORM_WIN32
#include "tnt_os_windows_entry.c"
#include "tnt_os_windows_impl.c"
#endif

#include <SDL2/SDL.h>

u64 os_time_now(void) { return SDL_GetPerformanceCounter(); }

u64 os_time_frequency(void) { return SDL_GetPerformanceFrequency(); }

String8 os_file_read(String8 path) {
    String8 result = {0};
    FILE *file = fopen(str8_to_char(path), "r");
    if (file == 0) {
        fseek(file, 0, SEEK_END);
        result.size = ftell(file) - 1;
        result.data = malloc(result.size);
        fseek(file, 0, SEEK_SET);
        fread(result.data, 1, result.size, file);
        fclose(file);
    }
    return result;
}
