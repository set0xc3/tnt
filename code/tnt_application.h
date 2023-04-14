#ifndef TNT_APPLICATION_H
#define TNT_APPLICATION_H

#include "tnt_types.h"
#include "tnt_linked_list.h"
#include "tnt_os.h"
#include "tnt_render.h"
#include "tnt_memory_arena.h"

typedef struct ApplicationState ApplicationState;
struct ApplicationState {
  b8              is_quit;
	TNT_Arena      *arena_permanent_storage;
	TNT_Arena      *arena_transient_storage;
  OS_Input       *input;
  TNT_Render     *render;
  OS_Window      *window;
  LinkedList_List event_list;  // OS_Event*
};

void application_init(void);
void application_run(void);
void application_on_event(OS_Event *event);
void application_process_events(void);

#endif // TNT_APPLICATION_H
