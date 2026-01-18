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

void change_chartype_color(chtype* ch, int color_pair)
{
    *ch &= A_CHARTEXT;
    *ch |= COLOR_PAIR(color_pair);
}

void draw_correct_input_formatted_char(DrawCommand* self, RenderContext* ctx) {
    chtype ch = self->c;
    change_chartype_color(&ch, COLOR_CORRECT);
    mvwaddch(ctx->win, ctx->cy, ctx->cx, ch);
    increment_cursor(ctx);
    redraw_cursor(ctx);
}

void draw_incorrect_input_formatted_char(DrawCommand* self, RenderContext* ctx) {
    chtype ch = mvwinch(ctx->win, ctx->cy, ctx->cx);
    ch = ((ch & A_CHARTEXT) == ' ') ? self->c : ch;
    change_chartype_color(&ch, COLOR_INCORRECT);
    mvwaddch(ctx->win, ctx->cy, ctx->cx, ch);
    increment_cursor(ctx);
    redraw_cursor(ctx);
}
/* does not delete the char. Resets the color to default so that it looks like the user's input is reverted. */
void delete_prev_char(DrawCommand* self, RenderContext* ctx)
{
    (void)self;
    decrement_cursor(ctx);
    chtype ch = mvwinch(ctx->win, ctx->cy, ctx->cx);
    change_chartype_color(&ch, COLOR_PRIMARY);
    mvwaddch(ctx->win, ctx->cy, ctx->cx, ch);
    redraw_cursor(ctx);
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

DrawCommand draw_command_from_input(const TypingTestInput* inp)
{
    if (inp->is_backspace) {
        return new_delete_char_command();
    } else if (!inp->is_correct) {
        return draw_incorrectly_inputted_command_new(inp->inputted);
    } else {
        return draw_correctly_inputted_command_new(inp->inputted);
    }
}