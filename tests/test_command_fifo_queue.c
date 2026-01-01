#include <unity.h>
#include "fifo_queue.h"

static FifoQueue q;

void setUp(void) {

    q = fifo_q_new();
}    // runs before each test
void tearDown(void) {} // runs after each test

void test_init_queue(void)
{
    TEST_ASSERT_NULL(q.first);
    TEST_ASSERT_NULL(q.last);
}
void test_add_one_command_stores_copy(void)
{
    DrawCommand d = new_draw_char_command('o');
    fifo_q_push(&q, &d, sizeof(DrawCommand));
    DrawCommand* inside = (DrawCommand*) q.first->cmd;
    TEST_ASSERT_NOT_EQUAL(&d, inside);
}

void test_pop_one_command(void)
{
    DrawCommand d = new_draw_char_command('h');
    fifo_q_push(&q, &d, sizeof(DrawCommand));
    DrawCommand* dd = (DrawCommand*)fifo_q_pop(&q);
    char c = dd->c;
    TEST_ASSERT_EQUAL_CHAR('h', c);
}

void test_pop_two_commands(void)
{
    DrawCommand d = new_draw_char_command('h');
    DrawCommand d2 = new_draw_char_command('j');
    fifo_q_push(&q, &d, sizeof(DrawCommand));
    fifo_q_push(&q, &d2, sizeof(DrawCommand));
    DrawCommand* dd = (DrawCommand*)fifo_q_pop(&q);
    DrawCommand* dd2 = (DrawCommand*)fifo_q_pop(&q);
    char c = dd->c;
    char c2 = dd2->c;
    TEST_ASSERT_EQUAL_CHAR('h', c);
    TEST_ASSERT_EQUAL_CHAR('j', c2);
}

int main() {
    RUN_TEST(test_add_one_command_stores_copy);
    RUN_TEST(test_init_queue);
    RUN_TEST(test_pop_one_command);
    RUN_TEST(test_pop_two_commands);
}