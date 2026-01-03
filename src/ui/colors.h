#ifndef COLORS_H
#define COLORS_H

enum ColorScheme {
    DEFAULT,
    TRON_ORANGE,
    GRUVBOX,
    CYBERPUNK_FEVER_DREAM
};

enum Color {
    COLOR_PRIMARY,
    COLOR_CORRECT,
    COLOR_INCORRECT
    // ,DETAIL
};

void init_color_scheme(int color_sheme);

#endif