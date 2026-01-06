#include "ui_commands.h"
#include "colors.h"

void draw_default_formatted_char(DrawCommand* self, RenderContext* ctx)
{
    // not needed. Used by default!!
    // self->c &= A_CHARTEXT;
    // self->c |= COLOR_PAIR(COLOR_PRIMARY);

    mvwaddch(ctx->win, ctx->cy, ctx->cx, self->c);
    increment_cursor(ctx);
}

void draw_correct_input_formatted_char(DrawCommand* self, RenderContext* ctx) {
    (void)self;

    chtype ch = mvwinch(ctx->win, ctx->cy, ctx->cx);
    ch &= A_CHARTEXT;
    ch |= COLOR_PAIR(COLOR_CORRECT);
    mvwaddch(ctx->win, ctx->cy, ctx->cx, ch);

    increment_cursor(ctx);
}

void draw_incorrect_input_formatted_char(DrawCommand* self, RenderContext* ctx) {
    (void) self;

    chtype ch = mvwinch(ctx->win, ctx->cy, ctx->cx);
    ch &= A_CHARTEXT;
    ch |= COLOR_PAIR(COLOR_INCORRECT);
    mvwaddch(ctx->win, ctx->cy, ctx->cx, ch);

    increment_cursor(ctx);
}
/* does not delete the char. Resets the color to default so that it looks like the user's input is reverted. */
void delete_prev_char(DrawCommand* self, RenderContext* ctx)
{
    (void)self;

    decrement_cursor(ctx);

    chtype ch = mvwinch(ctx->win, ctx->cy, ctx->cx);

    ch &= A_CHARTEXT;
    ch |= COLOR_PAIR(COLOR_PRIMARY);
    mvwaddch(ctx->win, ctx->cy, ctx->cx, ch);
    wmove(ctx->win, ctx->cy, ctx->cx); // redraws the cursor

}

DrawCommand new_draw_char_command(char c)
{
    return (DrawCommand) {
        .c = (chtype)c,
        .execute = draw_default_formatted_char
    };
}

DrawCommand draw_correctly_inputted_command_new(char c) {
    return (DrawCommand) {
        .c = (chtype)c,
        .execute = draw_correct_input_formatted_char
    };
}

DrawCommand draw_incorrectly_inputted_command_new(char c) {
    return (DrawCommand) {
        .c = (chtype)c,
        .execute = draw_incorrect_input_formatted_char
    };
}

DrawCommand  new_delete_char_command()
{
    return (DrawCommand) {
        .c = (chtype)'\b',
        .execute = delete_prev_char
    };
}

static inline bool is_backspace(int ch)
{
    return ch == KEY_BACKSPACE || ch == KEY_DC || ch == 127 || ch == '\b';
}

DrawCommand draw_command_from_input(const TypingTestInput* inp)
{
    if (is_backspace(inp->inputted)) {
        return new_delete_char_command();
    } else if (!inp->is_correct) {
        return draw_incorrectly_inputted_command_new(inp->inputted);
    } else {
        return draw_correctly_inputted_command_new(inp->inputted);
    }
}