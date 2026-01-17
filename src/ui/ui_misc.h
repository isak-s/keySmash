#ifndef UI_MISC_H
#define UI_MISC_H

#include <ncurses.h>
#include "domain/typing_test.h"

void ui_draw_typing_test_time_left(TypingTest* tt, WINDOW* border_win, int max_x);

#endif