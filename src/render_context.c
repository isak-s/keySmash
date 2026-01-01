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