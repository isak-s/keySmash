#include <unity.h>
#include "fifo_queue.h"

void setUp(void) {}    // runs before each test
void tearDown(void) {} // runs after each test

void test_init_queue(void)
{
    FifoQueue q = fifo_q_new();

    TEST_ASSERT_NULL(q.first);
    TEST_ASSERT_NULL(q.last);
}

void test_pop_one_command(void)
{

    FifoQueue q = fifo_q_new();

    DrawCommand d = new_draw_char_command('h');
    fifo_q_push(&q, &d);
    DrawCommand* dd = (DrawCommand*)fifo_q_pop(&q);
    char c = dd->c;
    TEST_ASSERT_EQUAL_CHAR('h', c);
}

int main() {
    RUN_TEST(test_init_queue);
    RUN_TEST(test_pop_one_command);
}