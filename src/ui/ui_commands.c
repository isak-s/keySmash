#include "ui_commands.h"

// Cursor movement lives in executor by mutating ctx

void draw_default_formatted_char(DrawCommand* self, RenderContext* ctx)
{
    mvwaddch(ctx->win, ctx->cy, ctx->cx, self->c);
}

void draw_correct_input_formatted_char(DrawCommand* self, RenderContext* ctx) {
    (void)self;

    chtype ch = mvwinch(ctx->win, ctx->cy, ctx->cx);
    ch &= A_CHARTEXT;
    ch |= COLOR_PAIR(1);
    mvwaddch(ctx->win, ctx->cy, ctx->cx, ch);
}

void draw_incorrect_input_formatted_char(DrawCommand* self, RenderContext* ctx) {
    (void) self;

    chtype ch = mvwinch(ctx->win, ctx->cy, ctx->cx);
    ch &= A_CHARTEXT;
    ch |= COLOR_PAIR(2);
    mvwaddch(ctx->win, ctx->cy, ctx->cx, ch);
}

void delete_prev_char(DrawCommand* self, RenderContext* ctx)
{
    // move to prev and delete
    // win->_curx - 1 and check boundaries
    (void)self;
    decrement_cursor(ctx);
    // restore default color

    // as of right now, the pos is incremented regardless of what command
    //      so this is a quick and ugly fix for that.
    decrement_cursor(ctx);
}

DrawCommand new_draw_char_command(char c)
{
    return (DrawCommand) {
        .c = c,
        .execute = draw_default_formatted_char
    };
}

DrawCommand draw_correctly_inputted_command_new(char c) {
    return (DrawCommand) {
        .c = c,
        .execute = draw_correct_input_formatted_char
    };
}

DrawCommand draw_incorrectly_inputted_command_new(char c) {
    return (DrawCommand) {
        .c = c,
        .execute = draw_incorrect_input_formatted_char
    };
}

DrawCommand  new_delete_char_command()
{
    return (DrawCommand) {
        .c = '\b',
        .execute = delete_prev_char
    };
}

DrawCommand draw_command_from_input(TypingTestInput* inp)
{
    if (inp->inputted == KEY_BACKSPACE || inp->inputted == KEY_DC) {
        return new_delete_char_command();
    } else if (!inp->is_correct) {
        return draw_incorrectly_inputted_command_new(inp->inputted);
    } else {
        return draw_correctly_inputted_command_new(inp->inputted);
    }
}