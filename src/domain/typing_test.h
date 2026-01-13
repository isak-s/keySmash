#ifndef TYPING_TEST_H
#define TYPING_TEST_H

#include "storage/fifo_queue.h"
#include "ui/render_context.h"
#include "typing_test_input.h"

typedef struct {
    int64_t  start_timestamp;
    char* text;
    char* language;
    size_t idx;

    FifoQueue draw_queue;
    FifoQueue input_history;
} TypingTest;


TypingTest typing_test_new_english(char* text);

TypingTestInput get_input(TypingTest* tt, RenderContext* ctx);

void typing_test_execute_draw_queue(TypingTest* tt, RenderContext* ctx);

#endif