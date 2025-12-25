#include "unity.h"
#include "screenpos.h"

void setUp(void) {}    // runs before each test
void tearDown(void) {} // runs after each test

void test_set_screen_pos(void)
{
    ScreenPos pos = new_screen_pos();

    set_screen_pos(&pos, 10, 10);
    TEST_ASSERT_EQUAL_INT32(pos.x, 10);
    TEST_ASSERT_EQUAL_INT32(pos.y, 10);
}

int main() {
  RUN_TEST(test_set_screen_pos);
}