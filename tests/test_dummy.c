#include "unity.h"
#include "dummy.h"
void setUp(void) {}    // runs before each test
void tearDown(void) {} // runs after each test

void test_dummy_adds() {
    int a = 1;
    int b = 2;
    int res = add(a, b);
    TEST_ASSERT_EQUAL_INT32(res, a + b);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_dummy_adds);
    return UNITY_END();
}