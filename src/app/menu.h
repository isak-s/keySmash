#ifndef MENU_H
#define MENU_H

#include "backend/ui_element.h"
#include <stddef.h>
#include <stdbool.h>
#include "ui/ui_panel_curses.h"
#include "domain/statistics.h"
#include "backend/menu_input.h"
#include "app_context.h"

typedef void (*MenuAction)(AppContext* app_state);

typedef struct {
    const char* text;
    bool enabled;
    int row;
    MenuAction action;
} MenuItem;

typedef struct {
    char* text;
    bool enabled;
    int row;
    Statistics* stat;
} StatisticsItem;

// MenuItem* menu_item_create(const char* text);

UIPanelCurses menu_main_create(int max_x);

void handle_menu_input(UIPanelCurses* menu, MenuInput* inp, AppContext* app_state);

UIPanelCurses statistics_panel_create(int max_x, int y, Statistics* stat);

#endif
