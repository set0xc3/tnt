#if !defined(TNT_OS_H)
#define TNT_OS_H

#include "tnt_base_types.h"
#include "tnt_string.h"

enum OS_EventType {
  OS_EVENT_KIND_NONE,
  OS_EVENT_KIND_APP_QUIT,
  OS_EVENT_KIND_KEY_CODE,
  OS_EVENT_KIND_MOUSE_BUTTON,
  OS_EVENT_KIND_MOUSE_SCROLLED,
  OS_EVENT_KIND_MOUSE_MOTION,
  OS_EVENT_KIND_WINDOW_RESIZED,
  OS_EVENT_KIND_WINDOW_MOVED,
  OS_EVENT_KIND_COUNT
};

typedef struct OS_Event OS_Event;
struct OS_Event {
  u32 kind;
  i32 state;
  u32 code;
  f32 mouse_x, mouse_y;
  f32 mouse_wheel_y;
  i32 window_width, window_height;
};

enum OS_KeyCode {
  OS_KEYCODE_NONE,
  OS_KEYCODE_A,
  OS_KEYCODE_D,
  OS_KEYCODE_S,
  OS_KEYCODE_W,
  OS_KEYCODE_Q,
  OS_KEYCODE_E,
  OS_KEYCODE_ESCAPE,
  OS_KEYCODE_COUNT
};

enum OS_MouseButton {
  OS_MOUSE_BUTTON_NONE,
  OS_MOUSE_BUTTON_LEFT,
  OS_MOUSE_BUTTON_MIDDLE,
  OS_MOUSE_BUTTON_RIGHT,
  OS_MOUSE_BUTTON_COUNT
};

typedef struct OS_Input OS_Input;
struct OS_Input {
  b32 last_key[OS_KEYCODE_COUNT];
  b32 key[OS_KEYCODE_COUNT];

  b32 last_button[OS_MOUSE_BUTTON_COUNT];
  b32 button[OS_MOUSE_BUTTON_COUNT];

  f32 mouse_x, mouse_y;
  f32 mouse_delta_x, mouse_delta_y;
  f32 mouse_wheel_y;
};

typedef struct OS_Window OS_Window;
struct OS_Window {
  const char* title;
  u32 width, height;
  u32 xpos, ypos;
  void* handle;
  void* render;

  void (*event_callback)(OS_Event* event);
};

void os_init(void);
void os_shutdown(void);

void* os_memory_alloc(void* start, const u64 size);
void os_memory_free(void* memory, const u64 size);

u64 os_page_size(void);
void os_sleep(u32 milliseconds);

u64 os_time_now(void);
u64 os_time_frequency(void);

void* os_library_load(String8 path);
void* os_library_load_symbol(void* library_handle, String8 name);
void os_library_unload(void* library_handle);

void os_input_on_event(OS_Input* input, OS_Event* event);
void os_input_update(OS_Input* input);
b8 os_input_key_pressed(OS_Input* input, u32 code);
b8 os_input_key_down(OS_Input* input, u32 code);
b8 os_input_key_up(OS_Input* input, u32 code);
b8 os_input_button_pressed(OS_Input* input, u32 code);
b8 os_input_button_down(OS_Input* input, u32 code);
b8 os_input_button_up(OS_Input* input, u32 code);
void os_input_get_mouse_position(OS_Input* input, f32* xpos, f32* ypos);
void os_input_get_mouse_delta(OS_Input* input, f32* xdelta, f32* ydelta);
f32 os_input_get_mouse_scroll_y(OS_Input* input);

b8 os_window_open(OS_Window* window, const char* title, u32 width, u32 height,
                  u32 xpos, u32 ypos);
void os_window_close(OS_Window* window);
void os_window_poll_events(OS_Window* window);
void os_window_set_event_callback(OS_Window* window, void* function);
void os_window_set_title(OS_Window* window, String8 title);

String8 os_file_read(String8 path);

#endif  // TNT_OS_H
