
typedef struct Window Window;
struct Window {
	void (*event_callback)(void);
};

global_variable Window *window = 0;

internal void window_set_event_callback(Window *window, void *callback)
{
	window->event_callback = callback;
}

internal void app_on_event(void)
{
	LOG_DEBUG("[window] -> [app] OnEvent");
}

internal void test_callbacks(void)
{
	window = malloc(sizeof(Window));
	
	window_set_event_callback(window, app_on_event);
	
	window->event_callback();
}