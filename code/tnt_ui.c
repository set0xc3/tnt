#include "tnt_ui.h"

UI_Widget *UI_WidgetMake(UI_WidgetFlags flags, String8 string) {
	UI_Widget *result = 0;
	return result;
}

UI_Widget *UI_WidgetMakeF(UI_WidgetFlags flags, char *fmt, ...) {
	UI_Widget *result = 0;
	return result;
}

UI_Widget *UI_PushParent(UI_Widget *widget) {
	UI_Widget *result = 0;
	return result;
}

UI_Widget *UI_PopParent(void) {
	UI_Widget *result = 0;
	return result;
}

UI_Comm UI_CommFromWidget(UI_Widget *widget) {
	UI_Comm result = {0};
	return result;
}

UI_Comm UI_ButtonF(String8 string) {
	UI_Widget *widget = UI_WidgetMake(UI_WIDGET_FLAG_CLICKABLE|
                                    UI_WIDGET_FLAG_DRAW_BORDER|
                                    UI_WIDGET_FLAG_DRAW_TEXT|
                                    UI_WIDGET_FLAG_DRAW_BACKGROUND,
                                    string);
	UI_Comm comm = UI_CommFromWidget(widget);
	return comm;
}
