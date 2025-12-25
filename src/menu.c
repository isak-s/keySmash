#include "menu.h"
// only include adapters in the c file to avoid circular dependencies
#include "menu_adapter.h"
#include "screenpos.h"
#include "assert.h"

void menu_add_item(Menu* menu, const char* text)
{
    assert(menu->count <= menu->capacity);
    menu->items[menu->count++] = (MenuItem){
        .text = text
    };
}

UIElement ui_menu_item_from_menu(const Menu* menu, size_t index, ScreenPos pos)
{
    // wraps the menu item at the index in a UIElement and returns.
    return ui_menu_item_create(&menu->items[index], pos);
}


void menu_item_draw(const MenuItem* item, const ScreenPos* pos)
{
    (void) item;
    (void) pos;
}

void label_draw(const Label* label, const ScreenPos* pos)
{
    (void) label;
    (void) pos;
}

void menu_draw(const Menu* menu, const ScreenPos* pos)
{
    (void) menu;
    (void) pos;
}
void menu_move_up(Menu menu)
{
    (void) menu;
}
void menu_move_down(Menu menu)
{
    (void) menu;
}

Menu* start_menu_create()
{
    Menu* menu = malloc(sizeof(Menu));
    menu->count = 0;
    menu->selected = 0;
    menu->capacity = 3;
    menu->items = malloc(sizeof(MenuItem) * 3);
    menu_add_item(menu, "select mode");
    menu_add_item(menu, "statistics");
    menu_add_item(menu, "start test");
    menu->pos = new_screen_pos();
    return menu;
}

void menu_destroy(Menu* menu)
{
    free(menu->items);
    menu->items = NULL;
    menu->capacity = 0;
    menu->count = 0;
    menu->selected = 0;
}

Menu* in_game_menu_create()
{
    // dummy
    Menu* m = malloc(sizeof(Menu));
    return m;
}