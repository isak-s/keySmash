#ifndef MENU_ADAPTER_H
#define MENU_ADAPTER_H

#include "ui_element.h"
#include "menu.h"

UIElement ui_menu_create(Menu *menu, ScreenPos pos);

UIElement ui_label_create(Label* label, ScreenPos pos);

UIElement ui_menu_item_create(MenuItem* Menu_item, ScreenPos pos);
#endif