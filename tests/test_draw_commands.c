#include <unity.h>
#include "ui/ui_commands.h"


void setUp(void) {}    // runs before each test
void tearDown(void) {} // runs after each test

void draw_correct_input_formatted_char(DrawCommand* self, RenderContext* ctx);
void draw_incorrect_input_formatted_char(DrawCommand* self, RenderContext* ctx);
void delete_prev_char(DrawCommand* self, RenderContext* ctx);

void test_draw_command_from_correct_char_input()
{
    TypingTestInput inp = (TypingTestInput) {
        .inputted = 'a',
        .is_correct = true,
        .time_since_test_start = 0
    };
    DrawCommand dc = draw_command_from_input(&inp);
    TEST_ASSERT_EQUAL_PTR(dc.execute, draw_correct_input_formatted_char);
}

void test_draw_command_from_incorrect_char_input()
{
    TypingTestInput inp = (TypingTestInput) {
        .inputted = 'a',
        .is_correct = false,
        .time_since_test_start = 0
    };
    DrawCommand dc = draw_command_from_input(&inp);
    TEST_ASSERT_EQUAL_PTR(dc.execute, draw_incorrect_input_formatted_char);
}

void test_draw_command_from_backspace_input()
{
    TypingTestInput inp = (TypingTestInput) {
        .inputted = KEY_BACKSPACE,
        .is_correct = true,
        .time_since_test_start = 0,
        .is_backspace = true
    };
    DrawCommand dc = draw_command_from_input(&inp);
    TEST_ASSERT_EQUAL_PTR(dc.execute, delete_prev_char);
}

int main()
{
    RUN_TEST(test_draw_command_from_correct_char_input);
    RUN_TEST(test_draw_command_from_incorrect_char_input);
    RUN_TEST(test_draw_command_from_backspace_input);
}