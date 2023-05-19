#include "tnt_linked_list.h"
#if !defined(TNT_APPLICATION_H)
#define TNT_APPLICATION_H

#include "tnt_base_types.h"
#include "tnt_memory_arena.h"
#include "tnt_os.h"
#include "tnt_render.h"
#include "tnt_scene.h"
#include "tnt_ui.h"

typedef struct EventList {
  LinkedListList list;
} EventList;

typedef struct AppState {
  MemoryArena *arena_permanent_storage;
  MemoryArena *arena_transient_storage;

  b8 is_quit;

  OS_Input *input;
  RenderContext *render;
  OS_Window *window;

  EventList event_list;
  u64 events_list_idx;

  UI_State *ui;
  Scene *scene;
} AppState;

void app_init(void);
void app_run(void);
void app_on_event(OS_Event *event);
void app_process_events(void);

void app_push_event(OS_Event *event);
void app_pop_event(void);
OS_Event *app_get_event(u64 index);

#endif  // TNT_APPLICATION_H
