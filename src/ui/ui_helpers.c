#include "ui_helpers.h"
#include "ncurses.h"


void clear_test_area(RenderContext* ctx)
{
    wclear(ctx->win);
}
// void refresh_panel(UIPanelCurses* panel)
// {
// }
void refresh_test_area(RenderContext* ctx)
{
    wrefresh(ctx->win);
}
void draw_panel(UIPanelCurses *panel)
{
    ui_panel_curses_draw(panel);
}
// void redraw_cursor(RenderContext* ctx)
// {
    // redraw_cursor(ctx);
// }