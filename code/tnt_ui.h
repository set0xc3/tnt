#if !defined(TNT_UI_H)
#define TNT_UI_H

#include "tnt_types.h"
#include "tnt_vector.h"
#include "tnt_render.h"

#define UI_LAYOUTS_CAPACITY 256

typedef u64 UI_Id;

typedef u32 UI_LayoutKind;
enum
{
	UI_LayoutKind_Horizontal,
	UI_LayoutKind_Vertical
};

typedef struct UI_Layout UI_Layout;
struct UI_Layout
{
	UI_LayoutKind kind;
	Vec2F32       pos;
	Vec2F32       size;
	f32	          pad;
};

typedef struct UI_State UI_State;
struct UI_State 
{
	Vec2F32   mouse_pos;
	b32			  mouse_button;
	UI_Id 	  active_id;
	UI_Layout layouts[UI_LAYOUTS_CAPACITY];
	u64       layouts_count;
};

void       ui_begin(UI_State *ctx, Vec2F32 pos);
void       ui_begin_layout(UI_LayoutKind kind);
b32        ui_button(UI_State *ctx, TNT_Render *render, Vec4F32 color, Vec2F32 size, UI_Id id);
void       ui_end_layout();
void       ui_end(UI_State *ctx);

void       ui_layout_push(UI_State *ctx, UI_Layout layout);
void       ui_layout_push_widget(UI_Layout *layout, Vec2F32 size);
UI_Layout *ui_layout_pop(UI_State *ctx);
UI_Layout *ui_layout_top(UI_State *ctx);
Vec2F32    ui_layout_available_pos(UI_Layout *layout);

#endif // TNT_UI_H