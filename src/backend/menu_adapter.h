#ifndef MENU_ADAPTER_H
#define MENU_ADAPTER_H

#include "backend/ui_element.h"
#include "app/menu.h"

// Draw MenuItem inside a UIPanelCurses
void menu_item_draw_adapter(UIElement* el, void* ctx);

// Create UIElement for a MenuItem
UIElement ui_menu_item_create(MenuItem* item);

UIElement ui_statistics_wpm_item_create(StatisticsItem* item);

UIElement ui_statistics_incorrect_item_create(StatisticsItem* item);

UIElement ui_statistics_currword_item_create(StatisticsItem* item);

#endif
