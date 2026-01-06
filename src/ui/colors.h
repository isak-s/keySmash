#ifndef COLORS_H
#define COLORS_H

#include <ncurses.h>

enum ColorScheme {
    DEFAULT,
    TRON_ORANGE,
    GRUVBOX,
    CYBERPUNK_FEVER_DREAM
};

enum Color {
    COLOR_TERM_DEFAULT,
    COLOR_PRIMARY,
    COLOR_CORRECT,
    COLOR_INCORRECT
    // ,DETAIL
};

void init_color_scheme(WINDOW* win, int color_sheme);

void set_color_scheme(WINDOW* win, int color_scheme);

#endif