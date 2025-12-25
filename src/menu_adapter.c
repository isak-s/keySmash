#include "menu_adapter.h"

static void menu_draw_adapter(const UIElement* el)
{
    const Menu *menu = el->impl;
    menu_draw(menu, &el->pos);
}

UIElement ui_menu_create(Menu *menu, ScreenPos pos)
{
    return (UIElement) {
        .pos = pos,
        .draw = menu_draw_adapter,
        .resize = NULL,
        .impl = menu
    };
}

// same for labels and graphs.

static void label_draw_adapter(const UIElement* el)
{
    const Label* label = el->impl;
    label_draw(label, &el->pos);
}

UIElement ui_label_create(Label* label, ScreenPos pos)
{
    return (UIElement) {
        .pos = pos,
        .draw = label_draw_adapter,
        .resize = NULL,
        .impl = label
    };
}

static void menu_item_draw_adapter(const UIElement* el)
{
    const MenuItem* item = el->impl;
    menu_item_draw(item, &el->pos);
}

UIElement ui_menu_item_create(MenuItem* menu_item, ScreenPos pos)
{
    return (UIElement) {
        .pos = pos,
        .draw = menu_item_draw_adapter,
        .resize = NULL,
        .impl = menu_item
    };
}