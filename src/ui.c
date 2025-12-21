#include "ncurses.h"
#include "ui.h"

void ui_init(void)
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}

void ui_shutdown(void)
{
    endwin();
}

UiKey ui_get_key(void)
{
    int ch = getch();
    switch (ch)
    {
    case KEY_UP: return UI_KEY_UP;

    default:
        return UI_KEY_UNKNOWN;
    }
}

void ui_set_screen_pos(ScreenPos* pos, int x, int y)
{
    pos->x = x;
    pos->y = y;
}

void ui_draw_text(const ScreenPos* pos, const char* text)
{
    // handle screen resize and shi
    mvprintw(pos->y, pos->x, "%s", text);
}

void ui_refresh(void)
{
    refresh();
}

void ui_clear(void)
{
    clear();
}