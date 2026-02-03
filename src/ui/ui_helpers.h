#ifndef UI_HELPERS_H
#define UI_HELPERS_H

#include "render_context.h"
#include "ui_panel_curses.h"

void clear_test_area(RenderContext* ctx);

void refresh_test_area(RenderContext* ctx);

void draw_panel(UIPanelCurses *panel);

// void redraw_cursor(RenderContext* ctx);

#endif