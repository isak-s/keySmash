#include "colors.h"

#include <stdlib.h>

void init_default_color_sceme()
{
    init_pair(COLOR_CORRECT, COLOR_GREEN, -1);
    init_pair(COLOR_INCORRECT, COLOR_RED, -1);
}

void init_gruvbox_color_sceme()
{
    init_pair(COLOR_PRIMARY, 214, 234);
    init_pair(COLOR_CORRECT, 108, 234);
    init_pair(COLOR_INCORRECT, COLOR_RED, 234);
}

void init_tron_orange_color_scheme()
{
    init_pair(COLOR_PRIMARY, 214, 234);
    init_pair(COLOR_CORRECT, 222, 237);
    init_pair(COLOR_INCORRECT, COLOR_BLACK, 222);
}

void init_cyberpunk_fever_dream_color_scheme()
{
    // how to set default color?
    init_pair(COLOR_PRIMARY, COLOR_CYAN, -1);
    init_pair(COLOR_CORRECT, COLOR_MAGENTA, -1);
    init_pair(COLOR_INCORRECT, COLOR_YELLOW, -1);
}

void set_color_scheme(WINDOW* win, int color_scheme)
{
    switch (color_scheme)
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
    wbkgd(win, COLOR_PAIR(COLOR_PRIMARY));
    werase(win);
    wrefresh(win);
}

/* sets the color scheme to a predefined setting */
void init_color_scheme(WINDOW* win, int color_scheme)
{
    if (!has_colors())
    {
        endwin();
        fprintf(stderr, "Unsupported terminal! Terminal must support colors.");
        exit(1);
    }
    start_color();
    use_default_colors();

    set_color_scheme(win, color_scheme);
}

