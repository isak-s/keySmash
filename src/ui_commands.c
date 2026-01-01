#include "ui_commands.h"


void draw_default_formatted_char(DrawCommand* self, RenderContext* ctx)
{
    waddch(ctx->win, self->c);
}

void delete_prev_char(DrawCommand* self, RenderContext* ctx)
{
    // move to prev and delete
    // win->_curx - 1 and check boundaries
    (void)self;
    (void)ctx;

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

DrawCommand draw_command_from_input(TypingTestInput* inp)
{
    if (inp->inputted == KEY_BACKSPACE || inp->inputted == KEY_DC) {
        return new_delete_char_command();
    } else if (!inp->is_correct) {
        return new_draw_char_command(inp->inputted);  // draw_incorrect_char_command
    } else {
        return new_draw_char_command(inp->inputted);
    }
}