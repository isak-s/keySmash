#ifndef COLORS_H
#define COLORS_H

#include <ncurses.h>

typedef enum {
    DEFAULT,
    TRON_ORANGE,
    GRUVBOX,
    CYBERPUNK_FEVER_DREAM
} ColorScheme;

enum Color {
    COLOR_PRIMARY = 1,
    COLOR_CORRECT,
    COLOR_INCORRECT
    // ,DETAIL
};

void init_color_scheme(WINDOW* win, ColorScheme color_sheme);

void set_color_scheme(WINDOW* win, ColorScheme color_scheme);

#endif