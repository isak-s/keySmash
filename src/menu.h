#ifndef MENU_H
#define MENU_H

#include <stdlib.h>
#include <stdbool.h>

#include "screenpos.h"

// forward declaration for the adapter
typedef struct UIElement UIElement;

typedef struct {
    const char* text;
    bool enabled;
    int height;
    int width;
} MenuItem;

typedef struct {
    MenuItem* items;
    size_t count;
    size_t capacity;
    size_t selected;
    ScreenPos pos;
} Menu;

typedef struct {
    char* text;
} Label;


void menu_add_item(Menu* menu, const char* text);

UIElement ui_menu_item_from_menu(const Menu* menu, size_t index, ScreenPos pos);

void menu_item_draw(const MenuItem* item, const ScreenPos* pos);

void label_draw(const Label* label, const ScreenPos* pos);

void menu_draw(const Menu* menu, const ScreenPos* pos);
void menu_move_up(Menu menu);
void menu_move_down(Menu menu);

#endif