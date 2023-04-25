#if !defined(TNT_APPLICATION_H)
#define TNT_APPLICATION_H

#include "tnt_camera.h"
#include "tnt_memory_arena.h"
#include "tnt_os.h"
#include "tnt_render.h"
#include "tnt_types.h"
#include "tnt_ui.h"

#define OS_EVENTS_CAPACITY 256

typedef struct ApplicationState ApplicationState;
struct ApplicationState
{
  b8 is_quit;
  TNT_MemoryArena *arena_permanent_storage;
  TNT_MemoryArena *arena_transient_storage;
  OS_Input *input;
  TNT_Render *render;
  OS_Window *window;
  void *event_buffer;
  u64 events_count;
  UI_State *ui;
  Camera *camera;
};

void application_init(void);
void application_run(void);
void application_on_event(OS_Event *event);
void application_process_events(void);

#endif // TNT_APPLICATION_H
