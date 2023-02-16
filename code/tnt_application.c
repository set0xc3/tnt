
typedef struct ApplicationState ApplicationState;
struct ApplicationState
{
	b8 is_quit;
	
	OS_State  *os_state;
	OS_Window *os_window;
};
global_variable ApplicationState app_state;

internal void application_init(void)
{
	app_state.os_window = malloc(sizeof(*app_state.os_window));
	os_window_create(app_state.os_window, "TNT Engine", 1280, 720, 0, 0);
}

internal void application_run(void)
{
	while (!app_state.is_quit)
	{
		if (!os_window_poll_events(app_state.os_window))
			break;
		
		os_sleep(1);
	}
}
