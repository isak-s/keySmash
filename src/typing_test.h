#ifndef TYPING_TEST_H
#define TYPING_TEST_H

#include "fifo_queue.h"

typedef struct {
    long  start_timestamp;
    char* text;
    char* language;
    int idx;

    FifoQueue draw_queue;
    FifoQueue input_history;
} TypingTest;


TypingTest typing_test_new_english(char* text);

TypingTestInput get_input(TypingTest* tt);

void typing_test_execute_draw_queue(TypingTest* tt, RenderContext* ctx);

#endif