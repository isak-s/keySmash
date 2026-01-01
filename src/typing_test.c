#include "typing_test.h"
#include "typing_test_input.h"
#include "time.h"
#include <string.h>
#include <stdlib.h>

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
    // if there is no open space in the window, pass.
    DrawCommand* cmd = fifo_q_pop(&tt->draw_queue);
    while (cmd) {
        cmd->execute(cmd, ctx);
        free(cmd);
        cmd = fifo_q_pop(&tt->draw_queue);
        // if there is no space left in the window, break.
    }
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
TypingTestInput get_input(TypingTest* tt)
{
    TypingTestInput input;
    input.inputted = getch();
    input.time_since_test_start = time(NULL) - tt->start_timestamp;
    input.is_correct = (tt->text[tt->idx] == input.inputted);
    return input;
}
