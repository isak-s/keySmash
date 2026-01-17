#include "ui_misc.h"

#include <inttypes.h>
#include <string.h>

void ui_draw_typing_test_time_left(TypingTest* tt, WINDOW* border_win, int max_x)
{
    char seconds_left[20];
    int64_t remaining = typing_test_time_left(tt);
    snprintf(seconds_left, sizeof(seconds_left), " %" PRId64 " ", remaining / 1000);
    // this overwrites the border so will have to do something about that
    mvwprintw(border_win, 0, max_x + 2 - strlen(seconds_left), "%s", seconds_left);
    wrefresh(border_win);
}