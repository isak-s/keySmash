#include <unity.h>
#include <stdlib.h>
#include <string.h>

#include "domain/typing_test.h"
#include "ui/ui_commands.h"

void setUp(void) {
    srand(1234);
}    // runs before each test
void tearDown(void) {} // runs after each test


void test_typing_test_initializes_with_valid_state(void)
{
    TypingTest tt = typing_test_new_english();

    TEST_ASSERT_EQUAL_STRING("english", tt.language);
    TEST_ASSERT_NOT_NULL(tt.wordset);
    TEST_ASSERT_NOT_NULL(tt.get_next_word);

    TEST_ASSERT_EQUAL_UINT(0, tt.buf_start);
    TEST_ASSERT_TRUE(tt.buf_len > 0);
    TEST_ASSERT_TRUE(tt.buf_len <= TEXT_BUFFER_CAPACITY);

    TEST_ASSERT_EQUAL_UINT(0, tt.cursor);
}

void test_initial_buffer_contains_printable_text(void)
{
    TypingTest tt = typing_test_new_english();

    for (size_t i = 0; i < tt.buf_len; i++) {
        char c = typing_test_get_char(&tt, i);
        TEST_ASSERT_TRUE_MESSAGE(
            (c >= 32 && c <= 126),
            "buffer contains non-printable character"
        );
    }
}

void test_correct_input_advances_cursor(void)
{
    TypingTest tt = typing_test_new_english();

    char expected = typing_test_get_char(&tt, 0);

    TypingTestInput inp = typing_test_process_char(&tt, expected);

    TEST_ASSERT_TRUE(inp.is_correct);
    TEST_ASSERT_EQUAL(1, tt.cursor);
}
void test_incorrect_input_advances_cursor(void)
{
    TypingTest tt = typing_test_new_english();


    TypingTestInput inp = typing_test_process_char(&tt, 'q');

    TEST_ASSERT_FALSE(inp.is_correct);
    TEST_ASSERT_EQUAL(1, tt.cursor);
}


void test_buffer_slides_after_threshold(void)
{
    TypingTest tt = typing_test_new_english();

    size_t original_start = tt.buf_start;

    tt.cursor = TEXT_BUFFER_CAPACITY / 3 + 1;

    if (tt.cursor > TEXT_BUFFER_CAPACITY / 3) {
        tt.buf_start = (tt.buf_start + 1) % TEXT_BUFFER_CAPACITY;
        tt.buf_len--;
        tt.cursor--;
    }

    TEST_ASSERT_EQUAL(
        (original_start + 1) % TEXT_BUFFER_CAPACITY,
        tt.buf_start
    );
}

void test_buffer_refills_when_low(void)
{
    TypingTest tt = typing_test_new_english();

    tt.buf_len = TEXT_BUFFER_CAPACITY / 4;

    typing_test_refill_buffer(&tt);

    TEST_ASSERT_TRUE(tt.buf_len > TEXT_BUFFER_CAPACITY / 4);
    TEST_ASSERT_TRUE(tt.buf_len <= TEXT_BUFFER_CAPACITY);
}

void test_input_history_records_inputs(void)
{
    TypingTest tt = typing_test_new_english();

    TypingTestInput inp = {
        .inputted = 'a',
        .is_correct = true,
        .time_since_test_start = 10
    };

    fifo_q_push(&tt.input_history, &inp, sizeof(inp));

    TypingTestInput* popped = fifo_q_pop(&tt.input_history);

    TEST_ASSERT_NOT_NULL(popped);
    TEST_ASSERT_EQUAL_CHAR('a', popped->inputted);

    free(popped);
}

int main() {
    RUN_TEST(test_buffer_refills_when_low);
    RUN_TEST(test_buffer_slides_after_threshold);
    RUN_TEST(test_input_history_records_inputs);
    RUN_TEST(test_typing_test_initializes_with_valid_state);
    RUN_TEST(test_correct_input_advances_cursor);
    RUN_TEST(test_incorrect_input_advances_cursor);
}