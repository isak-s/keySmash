#ifndef APP_H
#define APP_H

#include <stdlib.h>
#include "ui_element.h"

typedef struct {
    int selected;
    int running;
    int window_height;
    int window_width;
} Appstate;

typedef struct {
    UIElement *elements;
    size_t count;
} Screen;


void app_init(Appstate* s);
void app_handle_key(Appstate* s, int key);

void on_app_screen_resized(Appstate* s);

#endif