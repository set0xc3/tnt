#ifndef TNT_INPUT_H
#define TNT_INPUT_H

typedef enum OS_Keycode OS_Keycode;
enum OS_Keycode 
{
	OS_KEYCODE_A,
	OS_KEYCODE_D,
	OS_KEYCODE_S,
	OS_KEYCODE_W,
	OS_KEYCODE_COUNT,
};

typedef enum OS_MouseButton OS_MouseButton;
enum OS_MouseButton 
{
	OS_MOUSE_BUTTON_LEFT,
	OS_MOUSE_BUTTON_RIGHT,
	OS_MOUSE_BUTTON_MIDDLE,
	OS_MOUSE_BUTTON_COUNT,
};

typedef struct OS_Input OS_Input;
struct OS_Input 
{
	OS_Keycode key_current[OS_KEYCODE_COUNT];
	OS_Keycode key_last[OS_KEYCODE_COUNT];
	
	OS_MouseButton button_current[OS_MOUSE_BUTTON_COUNT];
	OS_MouseButton button_last[OS_MOUSE_BUTTON_COUNT];
	
	f32 mouse_x, mouse_y;
	f32 mouse_delta_x, mouse_delta_y;
	f32 mouse_wheel_x, mouse_wheel_y;
};

TNT_API void os_input_on_event(OS_Input *input);
TNT_API void os_input_update(OS_Input *input);

TNT_API void os_input_key_pressed(OS_Input *input, u32 key);
TNT_API void os_input_key_down(OS_Input *input, u32 key);
TNT_API void os_input_key_up(OS_Input *input, u32 key);

TNT_API void os_input_button_pressed(OS_Input *input, u32 key);
TNT_API void os_input_button_dow(OS_Input *input, u32 key);
TNT_API void os_input_button_up(OS_Input *input, u32 key);

TNT_API void os_input_get_mouse_position(OS_Input *input, f32 *xpos, f32 *ypos);
TNT_API void os_input_get_mouse_delta(OS_Input *input, f32 *xdelta, f32 *ydelta);
TNT_API void os_input_get_mouse_scroll(OS_Input *input, f32 *xwheel, f32 *ywheel);

#endif //TNT_INPUT_H