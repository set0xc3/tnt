#if !defined(TNT_APPLICATION_H)
#define TNT_APPLICATION_H

#include "tnt_memory_arena.h"
#include "tnt_os.h"
#include "tnt_render.h"
#include "tnt_types.h"
#include "tnt_ui.h"
#include "tnt_scene.h"

#define OS_EVENTS_CAPACITY 256

typedef struct AppState AppState;
struct AppState
{
  b8 is_quit;
  TNT_MemoryArena *arena_permanent_storage;
  TNT_MemoryArena *arena_transient_storage;
  OS_Input *input;
  Render_State *render;
  OS_Window *window;
  OS_Event *events;
  u64 events_count;
  UI_State *ui;
  Scene *scene;
};

void app_init(void);
void app_run(void);
void app_on_event(OS_Event *event);
void app_process_events(void);

void app_push_event(OS_Event *event);
void app_pop_event();
OS_Event *app_get_event(u64 index);

#endif // TNT_APPLICATION_H
