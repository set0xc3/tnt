
TNT_API void os_input_on_event(OS_Input *input)
{
	LOG_DEBUG("[input] OnEvent");
	
	switch (event->type)
	{
		case OS_EVENT_MOUSE_BUTTON: 
		{
			
		} break;
		
		case OS_EVENT_MOUSE_MOTION:
		{
			
		} break;
	}
}

TNT_API void os_input_update(OS_Input *input)
{
	
}

TNT_API void os_input_key_pressed(OS_Input *input, u32 key)
{
	
}

TNT_API void os_input_key_down(OS_Input *input, u32 key)
{
	
}

TNT_API void os_input_key_up(OS_Input *input, u32 key)
{
	
}

TNT_API void os_input_button_pressed(OS_Input *input, u32 key)
{
	
}

TNT_API void os_input_button_dow(OS_Input *input, u32 key)
{
	
}

TNT_API void os_input_button_up(OS_Input *input, u32 key)
{
	
}

TNT_API void os_input_get_mouse_position(OS_Input *input, f32 *xpos, f32 *ypos)
{
	*xpos = input->mouse_x;
	*ypos = input->mouse_y;
}

TNT_API void os_input_get_mouse_delta(OS_Input *input, f32 *xdelta, f32 *ydelta)
{
	
}

TNT_API void os_input_get_mouse_scroll(OS_Input *input, f32 *xwheel, f32 *ywheel)
{
	
}