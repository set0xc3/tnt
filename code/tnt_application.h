#ifndef TNT_APPLICATION_H
#define TNT_APPLICATION_H

typedef struct ApplicationState ApplicationState;
struct ApplicationState {
	b8 is_quit;
	OS_Input* os_input;
	LinkedList_List window_list;
    LinkedList_List event_list;
};

internal void application_init(void);
internal void application_run(void);
internal void application_on_event(OS_Event* event);
internal void application_process_events(void);

#endif //TNT_APPLICATION_H