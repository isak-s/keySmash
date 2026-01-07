#include "render_context.h"

#include "ui_constants.h"

RenderContext render_context_new(WINDOW* win)
{
    return (RenderContext) { // everything has a border so x y is 1 1 to account for that
        .cx = 1,
        .cy = 1,
        .win = win,
        .nbr_scrolls = 0,  // this is ugly as shit. Typingtest tracks text idx via the render context and needs to know if we scrolled or not.
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
        if (ctx->cy == 1) {
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

void scroll_window_upwards(RenderContext* ctx)
{
    if (!ctx->cy) return; // if we are already at the top, don't scroll!
    wscrl(ctx->win, 1);
    ctx->cy--;
    ctx->nbr_scrolls++;
    redraw_cursor(ctx);
    wrefresh(ctx->win);
}