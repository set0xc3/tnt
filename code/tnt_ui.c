#include "tnt_ui.h"
#include "tnt_render.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void ui_begin(UI_State *ctx, Vec2 pos, f32 pad)
{
	UI_Layout layout = {0};
	layout.kind = UI_LayoutKind_Horizontal;
	layout.pos = pos;
	layout.pad = pad;
	ui_layout_push(ctx, layout);
}

void ui_begin_layout(UI_LayoutKind kind)
{
}

b32 ui_button(UI_State *ctx, TNT_Render *render, Vec4 color, Vec2 size, UI_Id id)
{
	ASSERT(ctx->layouts_count == 0 || ctx->layouts_count+1 > UI_LAYOUTS_CAPACITY);

	UI_Layout *layout = ui_layout_top(ctx);
	const Vec2 pos = ui_layout_available_pos(layout);
	const Vec4 rect1 = v4(pos.x, pos.y, size.x, size.y);
	const Vec4 rect2 = v4(ctx->mouse_pos.x, ctx->mouse_pos.y, 0.0f, 0.0f);

	b32 click = false;
	if (ctx->active_id == id)
	{
		if (!ctx->mouse_button)
		{
			if (
				rect1.x < rect2.x + rect2.w &&
				rect1.x + rect1.w > rect2.x &&
				rect1.y < rect2.y + rect2.z &&
				rect1.z + rect1.y > rect2.y)
			{
				ctx->active_id = 0;
				click = true;
			}
		}
	}
	else
	{
		if (ctx->mouse_button)
		{
			if (!ctx->active_id)
			{
				if (
					rect1.x < rect2.x + rect2.w &&
					rect1.x + rect1.w > rect2.x &&
					rect1.y < rect2.y + rect2.z &&
					rect1.z + rect1.y > rect2.y)
				{
					ctx->active_id = id;
				}
			}
		}
	}

	draw_rectangle(render, v2(rect1.x, rect1.y), v2(rect1.z, rect1.w), color);

	ui_layout_push_widget(layout, size);

	return click;
}

void ui_end_layout()
{
}

void ui_end(UI_State *ctx)
{
	ui_layout_pop(ctx);
}

Vec2 ui_layout_available_pos(UI_Layout *layout)
{
	Vec2 result = {0};
	switch (layout->kind)
	{
	case UI_LayoutKind_Horizontal:
	{
		result = v2_add(layout->pos, layout->size);
		result = v2_add(result, v2(layout->pad, layout->pad));
		result = v2_mul(result, v2(1.0f, 0.0f));
		return result;
	}
	case UI_LayoutKind_Vertical:
	{
		Vec2 result = {0};
		result = v2_add(layout->pos, layout->size);
		result = v2_add(result, v2(layout->pad, layout->pad));
		result = v2_mul(result, v2(0.0f, 1.0f));
		return result;
	}
	}
	return result;
}

void ui_layout_push(UI_State *ctx, UI_Layout layout)
{
	ASSERT(ctx->layouts_count+1 > UI_LAYOUTS_CAPACITY);

	ctx->layouts[ctx->layouts_count] = layout;
	ctx->layouts_count += 1;
}

void ui_layout_push_widget(UI_Layout *layout, Vec2 size)
{
	switch (layout->kind)
	{
	case UI_LayoutKind_Horizontal:
		layout->size.x = layout->size.x + size.x + layout->pad;
		layout->size.y = MAX(layout->size.y, size.y);
		break;
	case UI_LayoutKind_Vertical:
		layout->size.x = MAX(layout->size.x, size.x);
		layout->size.y = layout->size.y + size.y + layout->pad;
		break;
	}
}

void ui_layout_pop(UI_State *ctx)
{
	ASSERT(ctx->layouts_count == 0 || ctx->layouts_count+1 > UI_LAYOUTS_CAPACITY);

	UI_Layout *layout = ctx->layouts - ctx->layouts_count;
	memset(layout, 0, sizeof(UI_Layout));
	ctx->layouts_count -= 1;
}

UI_Layout *ui_layout_top(UI_State *ctx)
{
	ASSERT(ctx->layouts_count == 0 || ctx->layouts_count+1 > UI_LAYOUTS_CAPACITY);

	UI_Layout *result = 0;

	result = ctx->layouts - ctx->layouts_count-1;
	return result;
}
