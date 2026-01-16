#include "test_area.h"
#include "backend/ui_panel.h"
#include <stdlib.h>

UIPanelCurses test_area_create(int max_x, int min_y, int max_y)
{
    UIPanel* ta = malloc(sizeof(UIPanel));
    // no elements. Maybe refactor?
    ta->element_count = 0;
    ta->elements = NULL;

    ta->x = 5;
    ta->y = min_y;
    ta->height = max_y / 3; // 7
    ta->width = max_x - 10;
    return ui_panel_curses_create(ta);
}
