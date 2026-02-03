#include "menu_input.h"
#include "ui/ui_panel_curses.h"
#include "app/app_context.h"
#include "menu_panel.h"

void handle_menu_input(UIPanelCurses* menu, MenuInput* inp, AppContext* app)
{
    switch (inp->type)
    {
    case M_ARROW_DOWN:
        menu->panel->selected++;
        menu->panel->selected %= menu->panel->element_count;
        break;
    case M_ARROW_UP:
        menu->panel->selected--;
        if (menu->panel->selected < 0) {
            menu->panel->selected = menu->panel->element_count - 1;
        }
        break;
    case M_ENTER:
        MenuItem* item = menu->panel->elements[menu->panel->selected].impl;
        if (item->enabled) item->action(app);
    default:
        break;
    }
}
