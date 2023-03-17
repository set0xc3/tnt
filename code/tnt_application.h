#ifndef TNT_APPLICATION_H
#define TNT_APPLICATION_H

#include "tnt_types.h"
#include "tnt_linked_list.h"
#include "tnt_os.h"

typedef struct ApplicationState ApplicationState;
struct ApplicationState {
  b8 is_quit;
  OS_Input *os_input;
  LinkedList_List window_list;
  LinkedList_List event_list;
};

void application_init(void);
void application_run(void);
void application_on_event(OS_Event *event);
void application_process_events(void);

#endif // TNT_APPLICATION_H
