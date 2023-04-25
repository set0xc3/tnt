#include "tnt_os.h"
#include "tnt_logger.h"

void os_input_on_event(OS_Input *input, OS_Event *event)
{
  switch (event->type)
  {
  case OS_EVENT_TYPE_KEY_CODE:
    input->key[event->code] = event->state;
    break;
  case OS_EVENT_TYPE_MOUSE_BUTTON:
    input->button[event->code] = event->state;
    break;
  case OS_EVENT_TYPE_MOUSE_MOTION:
    input->mouse_x = event->mouse_x;
    input->mouse_y = event->mouse_y;
    break;
  }
}

void os_input_update(OS_Input *input)
{
  memcpy(input->last_key, input->key, sizeof(input->key));
  memcpy(input->last_button, input->button, sizeof(input->button));

  input->mouse_wheel_y = 0;
}

b8 os_input_key_pressed(OS_Input *input, u32 code)
{
  return input->last_key[code] && input->key[code];
}

b8 os_input_key_down(OS_Input *input, u32 code)
{
  return !input->last_key[code] && input->key[code];
}

b8 os_input_key_up(OS_Input *input, u32 code)
{
  return input->last_key[code] && !input->key[code];
}

b8 os_input_button_pressed(OS_Input *input, u32 code)
{
  return input->last_button[code] && input->button[code];
}

b8 os_input_button_down(OS_Input *input, u32 code)
{
  return !input->last_button[code] && input->button[code];
}

b8 os_input_button_up(OS_Input *input, u32 code)
{
  return input->last_button[code] && !input->button[code];
}

void os_input_get_mouse_position(OS_Input *input, f32 *xpos, f32 *ypos)
{
  *xpos = input->mouse_x;
  *ypos = input->mouse_y;
}

void os_input_get_mouse_delta(OS_Input *input, f32 *xdelta, f32 *ydelta)
{
}

f32 os_input_get_mouse_scroll_y(OS_Input *input)
{
  return input->mouse_wheel_y;
}
