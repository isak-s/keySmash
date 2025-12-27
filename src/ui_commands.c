#include "ui_commands.h"

void draw_default_formatted_char(DrawCommand* self, WINDOW* win)
{
    waddch(win, self->c);
}

void delete_prev_char(DrawCommand* self, WINDOW* win)
{
    // move to prev and delete
    // win->_curx - 1 and check boundaries

}

DrawCommand new_draw_char_command(char c)
{
    DrawCommand dc;
    dc.execute = draw_default_formatted_char;
    dc.c = c;
    return dc;
}

DrawCommand new_delete_char_command()
{
    // make a more general UICommand and have this inherit that
    DrawCommand dc;
    dc.execute = delete_prev_char;
    dc.c = '\0';
    return dc;
}