#ifndef STATISTICS_ITEM_DRAW_CURSES
#define STATISTICS_ITEM_DRAW_CURSES

#include "backend/ui_element.h"

void statistics_menu_wpm_draw_adapter(UIElement* el, void* ctx);

void statistics_menu_incorrect_draw_adapter(UIElement* el, void* ctx);

void statistics_menu_curr_word_draw_adapter(UIElement* el, void* ctx);

#endif