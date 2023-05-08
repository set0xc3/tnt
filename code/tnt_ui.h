#if !defined(TNT_UI_H)
#define TNT_UI_H

#include "tnt_base_types.h"
#include "tnt_math.h"
#include "tnt_render.h"

#define UI_LAYOUTS_CAPACITY 256

typedef u64 UI_Id;

typedef enum UI_LayoutKind UI_LayoutKind;
enum UI_LayoutKind { UI_LayoutKind_Horizontal, UI_LayoutKind_Vertical };

typedef struct UI_Layout UI_Layout;
struct UI_Layout {
  UI_LayoutKind kind;
  Vec2 pos;
  Vec2 size;
  f32 pad;
};

typedef struct UI_State UI_State;
struct UI_State {
  Vec2 mouse_pos;
  b32 mouse_button;
  UI_Id active_id;
  UI_Layout layouts[UI_LAYOUTS_CAPACITY];
  u64 layouts_count;
};

void ui_begin(UI_State *ctx, Vec2 pos, f32 pad);
void ui_begin_layout(UI_LayoutKind kind);
b32 ui_button(UI_State *ctx, RenderState *render, Vec4 color, Vec2 size,
              UI_Id id);
void ui_end_layout(void);
void ui_end(UI_State *ctx);

void ui_layout_push(UI_State *ctx, UI_Layout layout);
void ui_layout_push_widget(UI_Layout *layout, Vec2 size);
void ui_layout_pop(UI_State *ctx);
UI_Layout *ui_layout_top(UI_State *ctx);
Vec2 ui_layout_available_pos(UI_Layout *layout);

#endif  // TNT_UI_H
