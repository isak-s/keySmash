#include "typing_test.h"

#include "time.h"
#include <string.h>
#include <stdlib.h>

#include "ui/ui_commands.h"

void typing_test_init_draw_queue(TypingTest* tt)
{
    for (char* c = tt->text; *c != '\0'; c++) {
        DrawCommand dc = new_draw_char_command(*c);
        fifo_q_push(&tt->draw_queue, &dc, sizeof(DrawCommand));
    }
}

// when user is typing, we should shift everything once a line is completed so that we can print the rest. TODO for future
void typing_test_execute_draw_queue(TypingTest* tt, RenderContext* ctx)
{
    int prev_x = ctx->cx;
    int prev_y = ctx->cy;
    if (render_context_out_of_space(ctx)) return;

    DrawCommand* cmd = fifo_q_pop(&tt->draw_queue);
    while (cmd) {
        cmd->execute(cmd, ctx);

        // increment_cursor(ctx);

        if (render_context_out_of_space(ctx)) break;

        free(cmd);
        cmd = fifo_q_pop(&tt->draw_queue);
    }
    // set cursor to prev pos before drawing so that the user types over the text.
    ctx->cx = prev_x;
    ctx->cy = prev_y;
    wmove(ctx->win, ctx->cy, ctx->cx);

    wrefresh(ctx->win);
}

TypingTest typing_test_new_english(char* text)
{
    TypingTest tt = (TypingTest){
        .idx = 0,
        .language = "english",
        .text = text,
        .start_timestamp = time(NULL),
        .draw_queue = fifo_q_new(),
        .input_history = fifo_q_new()};
    typing_test_init_draw_queue(&tt);
    return tt;
}

/* This function will await until a char is inputted. Halts the rest of the program!!! */
TypingTestInput get_input(TypingTest* tt, RenderContext* ctx)
{
    // cx and cy are offset by 1 from the text index since they represent screen position and have to account for the border.
    int idx = (ctx->cx - 1) + (ctx->cy - 1) * (ctx->max_x);
    TypingTestInput input;
    input.inputted = getch();
    input.time_since_test_start = time(NULL) - tt->start_timestamp;
    input.is_correct = (tt->text[idx] == input.inputted);
    return input;
}
