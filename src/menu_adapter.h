#ifndef MENU_ADAPTER_H
#define MENU_ADAPTER_H

#include "ui_element.h"
#include "menu.h"
#include "ui_panel_curses.h"

// Draw MenuItem inside a UIPanelCurses
void menu_item_draw_adapter(UIElement* el, void* ctx);

// Create UIElement for a MenuItem
UIElement ui_menu_item_create(MenuItem* item);

#endif
