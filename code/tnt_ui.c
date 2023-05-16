#include "tnt_ui.h"

#include "tnt_base_types.h"
#include "tnt_logger.h"
#include "tnt_math.h"
#include "tnt_render.h"

void ui_begin(UI_State *ui, Vec2 pos, f32 pad) {}

b32 ui_button(UI_State *ui, Vec2 position, Vec2 size, Vec4 color, UI_Id id) {
  b32 result = false;

  UI_Command *cmd = ui_push_command(ui);
  cmd->position = position;
  cmd->size = size;
  cmd->color = color;

  f32 half_height = ui->window.size.y / 2.0f;
  f32 half_width = ui->window.size.x / 2.0f;
  Vec2 mouse_pos = ui->mouse.position;
  mouse_pos.x = mouse_pos.x - half_width;
  mouse_pos.y = -mouse_pos.y + half_height;

  Vec2 rect1_position = position;
  Vec2 rect1_size = size;

  Vec2 rect2_position = mouse_pos;
  Vec2 rect2_size = v2(0.0f, 0.0f);

  if (rect1_position.x < rect2_position.x + rect2_size.x &&
      rect1_position.x + rect1_size.x > rect2_position.x &&
      rect1_position.y < rect2_position.y + rect2_size.y &&
      rect1_position.y + rect1_size.y > rect2_position.y) {
    if (!ui->active_id) {
      ui->active_id = id;
      LOG_DEBUG("[EVENT] Button:In");
    }

    if (ui->active_id) {
      result = true;
    }
  } else {
    if (ui->active_id) {
      ui->active_id = 0;
      LOG_DEBUG("[EVENT] Button:Out");
    }
  }

  return result;
}

void ui_end(UI_State *ui) { ui->command_idx = 0; }

UI_Command *ui_push_command(UI_State *ui) {
  ASSERT(ui->command_idx + 1 > UI_COMMAND_CAPASITY)

  UI_Command *result = &ui->command_list[ui->command_idx];
  ui->command_idx += 1;

  return result;
}

void ui_pop_command(UI_State *ui) {
  if (ui->command_idx == 0) {
    return;
  }

  memset(&ui->command_list[ui->command_idx], 0, sizeof(UI_Command));

  ui->command_idx -= 1;
}

UI_Command *ui_get_command(UI_State *ui, u64 idx) {
  UI_Command *result = &ui->command_list[idx];

  return result;
}

u64 ui_get_command_count(UI_State *ui) { return ui->command_idx; }