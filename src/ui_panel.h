#ifndef UI_PANEL_H
#define UI_PANEL_H

#include "ui_element.h"
#include <stddef.h>

typedef struct {
    int width;
    int height;
    int x;
    int y;

    UIElement* elements;
    size_t element_count;
} UIPanel;

#endif
