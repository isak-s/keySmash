#include "typing_test.h"
#include "typing_test_input.h"
#include "time.h"
#include <string.h>

void typing_test_init_draw_queue(TypingTest* tt)
{
    for (char* c = tt->text; *c != '\0'; c++) {
        DrawCommand dc = new_draw_char_command(*c);
        fifo_q_push(&tt->draw_queue, &dc, sizeof(DrawCommand));
    }
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
