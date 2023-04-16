#if !defined(TNT_UI_H)
#define TNT_UI_H

#include "tnt_types.h"
#include "tnt_string.h"
#include "tnt_vector.h"

typedef u32 UI_WidgetFlags;
enum {
	UI_WIDGET_FLAG_CLICKABLE        = (1<<0),
	UI_WIDGET_FLAG_VIEW_SCROLL      = (1<<1),
	UI_WIDGET_FLAG_DRAW_TEXT        = (1<<2),
	UI_WIDGET_FLAG_DRAW_BORDER      = (1<<3),
	UI_WIDGET_FLAG_DRAW_BACKGROUND  = (1<<4),
	UI_WIDGET_FLAG_DRAW_DROP_SHADOW = (1<<5),
	UI_WIDGET_FLAG_CLIP             = (1<<6),
};

typedef u32 UI_WidgetKind;
enum {
	UI_WIDGET_KIND_NONE,
	UI_WIDGET_KIND_BUTTON,
	UI_WIDGET_KIND_CHECKBOX,
	UI_WIDGET_KIND_SLIDER,
	UI_WIDGET_KIND_COUNT,
};

typedef struct UI_Key UI_Key;
struct UI_Key {
};

typedef struct UI_Widget UI_Widget;
struct UI_Widget {
	// tree links
	UI_Widget *first;
	UI_Widget *last;
	UI_Widget *next;
	UI_Widget *prev;
	UI_Widget *parent;

	// hash links
	UI_Widget *hash_next;
	UI_Widget *hash_prev;

	// key+generation info
	UI_Key key;
	u64 last_frame_touched_index;

	// per-frame info provided by builders
	UI_WidgetKind  kind;
	UI_WidgetFlags flags;
	String8 string;
};

typedef struct UI_Comm UI_Comm;
struct UI_Comm {
	UI_Widget *widget;
	V2F32 mouse;
  V2F32 drag_delta;
  b8 clicked;
  b8 double_clicked;
  b8 right_clicked;
  b8 pressed;
  b8 released;
  b8 dragging;
  b8 hovering;
};

UI_Widget *UI_WidgetMake(UI_WidgetFlags flags, String8 string);
UI_Widget *UI_WidgetMakeF(UI_WidgetFlags flags, char *fmt, ...);
UI_Widget *UI_PushParent(UI_Widget *widget);
UI_Widget *UI_PopParent(void);
void       UI_PushTextColor(V4F32 color);
void       UI_PopTextColor();
void       UI_PushBackgroundColor(V4F32 color);
void       UI_PopBackgroundColor();
void       UI_PushWidgetSize(V4F32 size);
void       UI_PopWidgetSize();
UI_Comm    UI_CommFromWidget(UI_Widget *widget);
UI_Comm    UI_ButtonF(String8 string);

#define UI_DeferLoop(begin, end) for(int _i_ = ((begin), 0); !_i_; _i_ += 1, (end))
#define UI_TextColor(v) UI_DeferLoop(UI_PushTextColor(v), UI_PopTextColor())
#define UI_BackgroundColor(v) UI_DeferLoop(UI_PushBackgroundColor(v), UI_PopBackgroundColor())
#define UI_WidgetSize(v) UI_DeferLoop(UI_PushWidgetSize(v), UI_PopWidgetSize())

#endif // TNT_UI_H
