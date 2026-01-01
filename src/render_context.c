#include "render_context.h"

RenderContext render_context_new(WINDOW* win)
{
    return (RenderContext) { // everything has a border so x y is 1 1 to account for that
        .cx = 1,
        .cy = 1,
        .win = win,
        .max_x = getmaxx(win) - 1,  // because of the border
        .max_y = getmaxy(win) - 1  // because of the border
    };
}

void render_context_handle_screen_wrapping(RenderContext* ctx)
{
    ctx->cx++;
    if (ctx->cx >= ctx->max_x - 1) {
        ctx->cx = 1;
        ctx->cy++;
    }
}

bool render_context_out_of_space(RenderContext* ctx)
{
    return (ctx->cy >= ctx->max_y - 1);
}