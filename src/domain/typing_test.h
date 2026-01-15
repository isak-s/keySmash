#ifndef TYPING_TEST_H
#define TYPING_TEST_H

#include "storage/fifo_queue.h"
#include "ui/render_context.h"
#include "typing_test_input.h"
#define TEXT_BUFFER_CAPACITY 1028//512 //10 //512

struct TypingTest;
typedef char* (*RandomWordFn)(struct TypingTest*);

typedef struct TypingTest {
    int64_t     start_timestamp;
    const char* language;
    char        text_buf[TEXT_BUFFER_CAPACITY];

    size_t   buf_start;  // logical start
    size_t   buf_len;    // number of valind chars
    size_t   cursor;     // how many chars typed so far minus backspaces

    FifoQueue draw_queue;
    FifoQueue input_history;

    char** wordset;
    RandomWordFn get_next_word;  // different implementation for quote and rand
} TypingTest;


TypingTest typing_test_new_english();

void typing_test_handle_input(TypingTest* tt, TypingTestInput* input);

void typing_test_execute_draw_queue(TypingTest* tt, RenderContext* ctx);

void typing_test_destroy(TypingTest* tt);

// really only visible so i can test them:
void typing_test_refill_buffer(TypingTest* tt);
char typing_test_get_char(const TypingTest* tt, size_t idx);
#endif