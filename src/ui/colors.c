#include "colors.h"
#include <ncurses.h>
#include <stdlib.h>

void init_default_color_sceme()
{
    init_pair(1, COLOR_GREEN, -1); // 1 = pair number, -1 = default background
    init_pair(2, COLOR_RED, -1);   // 1 = pair number, -1 = default background
}

void init_gruvbox_color_sceme()
{
    init_pair(1, COLOR_BLUE, -1); // 1 = pair number, -1 = default background
    init_pair(2, COLOR_RED, -1);   // 1 = pair number, -1 = default background
}

void init_tron_orange_color_scheme()
{
    init_pair(1, COLOR_YELLOW, -1); // 1 = pair number, -1 = default background
    init_pair(2, COLOR_RED, -1);   // 1 = pair number, -1 = default background
}

void init_cyberpunk_fever_dream_color_scheme()
{
    // how to set default color?
    // init_pair(0, COLOR_CYAN, -1);     // maybe default idk
    init_pair(1, COLOR_MAGENTA, -1);  // 1 = pair number, -1 = default background
    init_pair(2, COLOR_YELLOW, -1);   // 1 = pair number, -1 = default background
}

/* sets the color scheme to a predefined setting */
void init_color_scheme(int color_sheme)
{
    if (!has_colors())
    {
        endwin();
        fprintf(stderr, "Unsupported terminal! Terminal must support colors.");
        exit(1);
    }
    start_color();
    use_default_colors();
    switch (color_sheme)
    {
    case GRUVBOX:
        init_gruvbox_color_sceme();
        break;
    case TRON_ORANGE:
        init_tron_orange_color_scheme();
        break;
    case CYBERPUNK_FEVER_DREAM:
        init_cyberpunk_fever_dream_color_scheme();
        break;
    case DEFAULT:
    default:
        init_default_color_sceme();
    }
}

