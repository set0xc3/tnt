typedef struct OS_Main OS_Main;
struct OS_Main 
{
	b8 is_quit;
};
global_variable OS_Main *ctx = 0;

internal void os_window_event_on(void)
{
	
}

internal void os_input_event_on(void)
{
	
}

internal void os_text_event_on(void)
{
	
}

internal void os_drop_files_on(void)
{
	
}

internal void os_rect_changed_on(void)
{
	
}

internal void os_main_setup(void)
{
	ctx = malloc(sizeof(OS_Main));
	
	os_init();
	
	OS_Window *os_window = os_window_create("TNT", 1280, 720, 0, 0);
	
	while (!ctx->is_quit)
	{
		os_window_poll_events(os_window);
		os_window_process_events(os_window);
		
		os_sleep(1);
	}
	
	os_shutdown();
}