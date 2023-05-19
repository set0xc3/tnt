#include "tnt_os.h"
#if !defined(TNT_UI_H)
#define TNT_UI_H

#include "tnt_base_types.h"
#include "tnt_math.h"

#define UI_COMMAND_CAPASITY 1000

typedef u64 UI_Id;

typedef struct UI_Command {
  Vec2 position;
  Vec2 size;
  Vec4 color;
} UI_Command;

typedef struct UI_State {
  UI_Id active_id;
  UI_Command command_list[UI_COMMAND_CAPASITY];
  u64 command_idx;

  struct {
    Vec2 position;
    b32 button[OS_MOUSE_BUTTON_COUNT];
    b32 last_button[OS_MOUSE_BUTTON_COUNT];
  } mouse;

  struct {
    Vec2 position;
    Vec2 size;
  } window;
} UI_State;

void ui_begin(UI_State *ui, Vec2 pos, f32 pad);
b32 ui_button(UI_State *ui, Vec2 position, Vec2 size, Vec4 color, UI_Id id);
void ui_end(UI_State *ui);

UI_Command *ui_push_command(UI_State *ui);
void ui_pop_command(UI_State *ui);

UI_Command *ui_get_command(UI_State *ui, u64 idx);
u64 ui_get_command_count(UI_State *ui);

#endif  // TNT_UI_H
