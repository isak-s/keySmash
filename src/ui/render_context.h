#ifndef RENDER_CONTEXT_H
#define RENDER_CONTEXT_H

#include <ncurses.h>

typedef struct {
    WINDOW* win;
    int cx;
    int cy;
    int max_x;
    int max_y;
} RenderContext;

RenderContext render_context_new(WINDOW* win);

void increment_cursor(RenderContext* ctx);

void decrement_cursor(RenderContext* ctx);

bool render_context_out_of_space(RenderContext* ctx);

#endif