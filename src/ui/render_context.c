#include "render_context.h"

#include "ui_constants.h"

RenderContext render_context_new(WINDOW* win)
{
    return (RenderContext) { // everything has a border so x y is 1 1 to account for that
        .cx = 1,
        .cy = 1,
        .win = win,
        .nbr_scrolls = 0,
        .max_x = getmaxx(win) - UI_BORDER_PADDING,  // because of the border
        .max_y = getmaxy(win) - UI_BORDER_PADDING  // because of the border
    };
}

void increment_cursor(RenderContext* ctx)
{
    // the cursor can never overflow.
    // The text will be shifted upward together with the cursor somewhere else
    ctx->cx++;
    if (ctx->cx > ctx->max_x) {
        ctx->cx = 1;
        ctx->cy++;
    }
}

void decrement_cursor(RenderContext* ctx)
{
    ctx->cx--;
    if (ctx->cx < 1) {
        if (ctx->cy == 0) {
            ctx->cx++;
            return;
        }
        ctx->cx = ctx->max_x;
        ctx->cy--;
    }
}

bool render_context_out_of_space(RenderContext* ctx)
{
    return (ctx->cy > ctx->max_y);  // y starts at 0
}

void redraw_cursor(RenderContext* ctx)
{
    wmove(ctx->win, ctx->cy, ctx->cx);
}

bool scroll_window_upwards(RenderContext* ctx)
{
    if (!ctx->cy) return false; // if we are already at the top, don't scroll!
    wscrl(ctx->win, 1);
    ctx->cy--;
    ctx->nbr_scrolls++;
    redraw_cursor(ctx);
    wrefresh(ctx->win);

    return true;
}
// always allowed except when there is no previous text
bool backspace_allowed(RenderContext* ctx)
{
    bool has_history = ctx->nbr_scrolls >= 1;
    bool at_line_start = ctx->cx == 1;
    bool at_first_line = ctx->cy == 0;
    bool at_second_line = ctx->cy == 1;
    if (at_line_start) {
        if (at_first_line) {
            return false;
        } else if (at_second_line && !has_history) {
            return false;
        }
    }
    return true;
}