#include "render_context.h"

#include "ui_constants.h"

RenderContext render_context_new(WINDOW* win)
{
    return (RenderContext) { // everything has a border so x y is 1 1 to account for that
        .cx = 1,
        .cy = 1,
        .win = win,
        .max_x = getmaxx(win) - UI_BORDER_PADDING,  // because of the border
        .max_y = getmaxy(win) - UI_BORDER_PADDING  // because of the border
    };
}

void increment_cursor(RenderContext* ctx)
{
    ctx->cx++;
    if (ctx->cx > ctx->max_x) {
        ctx->cx = 1;
        ctx->cy++;
    }
}

void decrement_cursor(RenderContext* ctx)
{
    ctx->cx--;
    if (ctx->cx <= 1) {
        ctx->cx = ctx->max_x;
        ctx->cy--;
    }
}

bool render_context_out_of_space(RenderContext* ctx)
{
    return (ctx->cy >= ctx->max_y);
}