#include "tnt_math.h"
#include "tnt_os.h"

void os_input_on_event(OS_Input *input, OS_Event *event) {
  switch (event->kind) {
    case OS_EVENT_KIND_KEY_CODE:
      input->key[event->code] = event->state;
      break;
    case OS_EVENT_KIND_MOUSE_BUTTON:
      input->button[event->code] = event->state;
      break;
  }
}

void os_input_on_mouse_motion(OS_Input *input, i32 xpos, i32 ypos) {
  input->mouse_x = xpos;
  input->mouse_y = ypos;
}

void os_input_update(OS_Input *input) {
  memcpy(input->last_key, input->key, sizeof(input->key));
  memcpy(input->last_button, input->button, sizeof(input->button));

  input->mouse_wheel_y = 0;
}

b8 os_input_key_pressed(OS_Input *input, u32 code) {
  return input->last_key[code] && input->key[code];
}

b8 os_input_key_down(OS_Input *input, u32 code) {
  return !input->last_key[code] && input->key[code];
}

b8 os_input_key_up(OS_Input *input, u32 code) {
  return input->last_key[code] && !input->key[code];
}

b8 os_input_button_pressed(OS_Input *input, u32 code) {
  return input->last_button[code] && input->button[code];
}

b8 os_input_button_down(OS_Input *input, u32 code) {
  return !input->last_button[code] && input->button[code];
}

b8 os_input_button_up(OS_Input *input, u32 code) {
  return input->last_button[code] && !input->button[code];
}

Vec2 os_input_get_mouse_position(OS_Input *input) {
  Vec2 result;
  result.x = input->mouse_x;
  result.y = input->mouse_y;

  return result;
}

Vec2 os_input_get_mouse_delta(OS_Input *input) {
  Vec2 result;
  result.x = input->mouse_delta_x;
  result.y = input->mouse_delta_y;

  return result;
}

f32 os_input_get_mouse_scroll_y(OS_Input *input) {
  return input->mouse_wheel_y;
}
