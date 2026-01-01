#include <unity.h>
#include <stdlib.h>
#include <string.h>

#include "domain/typing_test.h"
#include "ui/ui_commands.h"

void setUp(void) {}    // runs before each test
void tearDown(void) {} // runs after each test

void test_new_english_typing_test_stores_text()
{
    char* str = "this is a typing test";
    TypingTest tt = typing_test_new_english(str);
    TEST_ASSERT_EQUAL_STRING(str, tt.text);
}

void test_new_english_typing_test_generates_draw_queue()
{
    char* str = "this is a typing test";
    TypingTest tt = typing_test_new_english(str);
    TEST_ASSERT_TRUE(tt.draw_queue.first != NULL && tt.draw_queue.last != NULL);
}

void test_new_english_typing_test_generates_draw_queue_with_same_sequence_as_text()
{
    char* str = "this is a typing test";
    TypingTest tt = typing_test_new_english(str);

    size_t len = strlen(str);
    char* stored = malloc(len + 1);

    for (size_t i = 0; i < len; i++) {
        DrawCommand* dc = fifo_q_pop(&tt.draw_queue);
        TEST_ASSERT_NOT_NULL(dc);
        stored[i] = dc->c;

        free(dc);  // remember to free DrawCommands after they are executed!!!
    }
    stored[len] = '\0';
    TEST_ASSERT_EQUAL_STRING(str, stored);
}

void test_new_english_typing_test_empty_input_history()
{
    char* str = "this is a typing test";
    TypingTest tt = typing_test_new_english(str);
    TEST_ASSERT_TRUE(tt.input_history.first == NULL && tt.input_history.last == NULL);
}

void test_get_input_stores_typing_test_input_in_input_history() {
    TEST_ASSERT_TRUE(false);
}


int main() {
    RUN_TEST(test_new_english_typing_test_stores_text);
    RUN_TEST(test_new_english_typing_test_generates_draw_queue);
    RUN_TEST(test_new_english_typing_test_empty_input_history);
    RUN_TEST(test_new_english_typing_test_generates_draw_queue_with_same_sequence_as_text);
    RUN_TEST(test_get_input_stores_typing_test_input_in_input_history);
}