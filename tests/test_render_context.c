#include <unity.h>

#include "ui/render_context.h"

/* this will only run when a terminal is availible. Not CI-pipeline */

static RenderContext ctx;

void setUp(void) {
    ctx = render_context_new(stdscr);

    // screen is not initiated, and these will be set to -1 in the tests.
    // sets arbitrary fake size to be able to test
    ctx.max_x = 10;
    ctx.max_y = 10;
}    // runs before each test

void tearDown(void) {} // runs after each test

void test_render_context_new_with_stdscr_gets_correct_defaults()
{
    // cannot know max sizes in advance.
    // Would be too much work to write the correct abstraction around window and test
    TEST_ASSERT_EQUAL_INT32(1, ctx.cx);
    TEST_ASSERT_EQUAL_INT32(1, ctx.cy);
    TEST_ASSERT_TRUE(ctx.win == stdscr);
}

void test_increment_cursor_adds_one_to_x_and_zero_to_y_initially()
{
    increment_cursor(&ctx);

    TEST_ASSERT_EQUAL_INT32(2, ctx.cx);
    TEST_ASSERT_EQUAL_INT32(1, ctx.cy);
}

void test_increment_cursor_until_max_adds_only_to_x()
{
    ctx.max_x = 5;
    // increment cursor 4 times
    for (int i = 2; i < 4 + 2; i++) {
        increment_cursor(&ctx);
        TEST_ASSERT_EQUAL_INT32(i, ctx.cx);
    }

    TEST_ASSERT_EQUAL_INT32(1, ctx.cy);
}

void test_increment_cursor_to_max_resets_x_and_adds_one_to_y()
{
    ctx.max_x = 5;
    ctx.max_y = 5;
    // increment cursor 5 times
    for (int i = 0; i < 5; i++) {
        increment_cursor(&ctx);
    }

    TEST_ASSERT_EQUAL_INT32(1, ctx.cx);
    TEST_ASSERT_EQUAL_INT32(2, ctx.cy);
}

void test_increment_cursor_to_max_twice_resets_x_and_adds_two_to_y()
{
    ctx.max_x = 5;
    ctx.max_y = 5;
    // increment cursor 5 times
    for (int i = 0; i < 10; i++) {
        increment_cursor(&ctx);
    }

    TEST_ASSERT_EQUAL_INT32(1, ctx.cx);
    TEST_ASSERT_EQUAL_INT32(3, ctx.cy);
}

void test_decrement_cursor_subtracts_one_from_x_and_zero_from_y_when_x_above_one()
{
    ctx.cx = 3;
    decrement_cursor(&ctx);

    TEST_ASSERT_EQUAL_INT32(2, ctx.cx);
    TEST_ASSERT_EQUAL_INT32(1, ctx.cy);
}

void test_decrement_cursor_twice_subtracts_one_from_x_and_zero_from_y_when_x_above_one()
{
    ctx.cx = 3;
    decrement_cursor(&ctx);
    decrement_cursor(&ctx);

    TEST_ASSERT_EQUAL_INT32(1, ctx.cx);
    TEST_ASSERT_EQUAL_INT32(1, ctx.cy);
}

void test_decrement_cursor_beyond_min_x_y_once_x_y_is_one()
{
    ctx.cx = 2;
    decrement_cursor(&ctx);
    decrement_cursor(&ctx);

    TEST_ASSERT_EQUAL_INT32(1, ctx.cx);
    TEST_ASSERT_EQUAL_INT32(1, ctx.cy);
}

void test_decrement_cursor_beyond_min_x_y_twice_x_y_is_one()
{
    ctx.cx = 2;
    decrement_cursor(&ctx);
    decrement_cursor(&ctx);
    decrement_cursor(&ctx);

    TEST_ASSERT_EQUAL_INT32(1, ctx.cx);
    TEST_ASSERT_EQUAL_INT32(1, ctx.cy);
}

void test_increment_then_decrement_once_x_y_is_same()
{
    increment_cursor(&ctx);
    decrement_cursor(&ctx);

    TEST_ASSERT_EQUAL_INT32(1, ctx.cx);
    TEST_ASSERT_EQUAL_INT32(1, ctx.cy);
}

void test_increment_then_decrement_multiple_x_y_is_same()
{
    for (int i = 0; i < 10; i++) {
        increment_cursor(&ctx);
        decrement_cursor(&ctx);
    }

    TEST_ASSERT_EQUAL_INT32(1, ctx.cx);
    TEST_ASSERT_EQUAL_INT32(1, ctx.cy);
}

void test_increment_then_decrement_multiple_at_max_x_x_y_is_same()
{
    ctx.cx = ctx.max_x;

    for (int i = 0; i < 10; i++) {
        increment_cursor(&ctx);
        decrement_cursor(&ctx);
    }

    TEST_ASSERT_EQUAL_INT32(10, ctx.cx);
    TEST_ASSERT_EQUAL_INT32(1, ctx.cy);
}

int main()
{
    RUN_TEST(test_render_context_new_with_stdscr_gets_correct_defaults);
    RUN_TEST(test_increment_cursor_adds_one_to_x_and_zero_to_y_initially);
    RUN_TEST(test_increment_cursor_until_max_adds_only_to_x);
    RUN_TEST(test_increment_cursor_to_max_twice_resets_x_and_adds_two_to_y);
    RUN_TEST(test_decrement_cursor_subtracts_one_from_x_and_zero_from_y_when_x_above_one);
    RUN_TEST(test_decrement_cursor_twice_subtracts_one_from_x_and_zero_from_y_when_x_above_one);
    RUN_TEST(test_decrement_cursor_beyond_min_x_y_once_x_y_is_one);
    RUN_TEST(test_decrement_cursor_beyond_min_x_y_twice_x_y_is_one);
    RUN_TEST(test_increment_then_decrement_once_x_y_is_same);
    RUN_TEST(test_increment_then_decrement_multiple_x_y_is_same);
    RUN_TEST(test_increment_then_decrement_multiple_at_max_x_x_y_is_same);
}