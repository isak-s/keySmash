#ifndef STATISTICS_PANEL_H
#define STATISTICS_PANEL_H

#include "ui/ui_panel_curses.h"
#include "domain/statistics.h"

typedef struct {
    char* text;
    bool enabled;
    int row;
    Statistics* stat;
} StatisticsItem;

UIPanelCurses statistics_panel_create(int max_x, int y, Statistics* stat);

#endif