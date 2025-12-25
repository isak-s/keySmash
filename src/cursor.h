#ifndef CURSOR_H
#define CURSOR_H

#include "screenpos.h"
#include "color.h"
typedef struct {
    ScreenPos pos;
    Color color;
} Cursor;
#endif