#include "typing_test.h"
#include "storage/file_loader.h"
#include <string.h>
#include <stdlib.h>

#include "ui/ui_commands.h"
#include "clock_helper.h"

#include <time.h>

char typing_test_get_char(const TypingTest* tt, size_t idx)
{
    if (idx >= tt->buf_len) {
        return '\0';
    }
    return tt->text_buf[(tt->buf_start + idx) % TEXT_BUFFER_CAPACITY];
}

void typing_test_get_curr_word(TypingTest* tt, char out[32])
{
    int i = 0;
    char c;
    while ((c = typing_test_get_char(tt, tt->cursor + i)) != ' ' &&
           c != '\0' &&
           i < 32 - 1) {
        out[i++] = c;
    }
    out[i] = '\0';
}

void typing_test_append_word(TypingTest* tt, const char* word)
{
    for (const char* c = word; *c; c++) {
        tt->text_buf[(tt->buf_start + tt->buf_len) % TEXT_BUFFER_CAPACITY] = *c;
        tt->buf_len++;

        DrawCommand dc = new_draw_char_command(*c);
        fifo_q_push(&tt->draw_queue, &dc, sizeof(DrawCommand));

        if (tt->buf_len >= TEXT_BUFFER_CAPACITY) return;
    }
    // add space. Might be weird to handle the very last word. Not a problem for now
    tt->text_buf[(tt->buf_start + tt->buf_len) % TEXT_BUFFER_CAPACITY] = ' ';
    DrawCommand dc = new_draw_char_command(' ');
    fifo_q_push(&tt->draw_queue, &dc, sizeof(DrawCommand));
    tt->buf_len++;
}

void typing_test_refill_buffer(TypingTest* tt)
{
    while (tt->buf_len < TEXT_BUFFER_CAPACITY / 2) {
        const char* next = tt->get_next_word(tt);
        typing_test_append_word(tt, next);
    }
}
/*
void typing_test_init_draw_queue(TypingTest* tt)
{
    for (size_t i = 0; i < tt->buf_len; i++) {
        char c = typing_test_get_char(tt, i);
        if (c == '\0') return;
        DrawCommand dc = new_draw_char_command(c);
        fifo_q_push(&tt->draw_queue, &dc, sizeof(DrawCommand));
    }
}
*/
// when user is typing, we should shift everything once a line is completed so that we can print the rest. TODO for future
void typing_test_execute_draw_queue(TypingTest* tt, RenderContext* ctx)
{
    int prev_x = ctx->cx;
    int prev_y = ctx->cy;

    ctx->cx = ctx->last_x_drawn;
    ctx->cy = ctx->last_y_drawn;
    if (render_context_out_of_space(ctx)) return;

    DrawCommand* cmd = fifo_q_pop(&tt->draw_queue);
    while (cmd) {
        cmd->execute(cmd, ctx);
        free(cmd);

        if (render_context_out_of_space(ctx)) break;

        cmd = fifo_q_pop(&tt->draw_queue);
    }
    // set cursor to prev pos before drawing so that the user types over the text.
    ctx->last_x_drawn = ctx->cx;
    ctx->last_y_drawn = ctx->cy;
    ctx->cx = prev_x;
    ctx->cy = prev_y;
    wmove(ctx->win, ctx->cy, ctx->cx);
    redraw_cursor(ctx);
    wrefresh(ctx->win);
}

void typing_test_handle_input(TypingTest* tt, TypingTestInput* input)
{
    input->time_since_test_start = now_ms() - tt->start_timestamp;

    if (input->is_backspace) {
        if (tt->cursor > 0) {
            tt->cursor--;
        }
        input->is_correct = true;
    } else {
        if (tt->cursor > TEXT_BUFFER_CAPACITY / 3) {
            tt->buf_start = (tt->buf_start + 1) % TEXT_BUFFER_CAPACITY;
            tt->buf_len--;
            tt->cursor--;
        }

        int expected = typing_test_get_char(tt, tt->cursor);
        input->is_correct = (expected == input->inputted);
        tt->cursor++;
    }

    typing_test_refill_buffer(tt);
    fifo_q_push(&tt->input_history, &input, sizeof(TypingTestInput));
}

// add parameter words to exclude
char* get_random_word_english_200(TypingTest* self)
{
    int i = rand() % 200;
    return self->wordset[i];
}

char** init_english_200_wordset()
{
    char** wordset = malloc(sizeof(char*) * 200);
    for (int i = 0; i < 200; i++)
    {
        wordset[i] = malloc(20);
    }
    srand(time(NULL));
    load_words("wordsets/english200.txt", wordset, 200, 20);

    return wordset;
}

TypingTest typing_test_new_english()
{
    TypingTest tt = (TypingTest){
        .cursor = 0,
        .language = "english",
        .wordset = init_english_200_wordset(),
        .get_next_word = get_random_word_english_200,
        .start_timestamp = now_ms(),
        .draw_queue = fifo_q_new(),
        .input_history = fifo_q_new()};
    typing_test_refill_buffer(&tt);
    //typing_test_init_draw_queue(&tt);
    return tt;
}

void typing_test_destroy(TypingTest* tt)
{
    for (int i = 0; i < 200; i++) free(tt->wordset[i]);
    free(tt->wordset);
    fifo_q_destroy(&tt->draw_queue);
    fifo_q_destroy(&tt->input_history);
}