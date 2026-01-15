#include <unity.h>

#include "input_internals.h"

#include <stdlib.h>

void setUp(void) {}    // runs before each test
void tearDown(void) {} // runs after each test

void test_decode_input_creates_TypingTestInput_from_valid_char()
{
    InputEvent ev = decode_input('a');
    TEST_ASSERT_EQUAL(INPUT_TYPING, ev.type);
}

void test_decode_input_creates_MenuInput_from_valid_menu_input()
{
    InputEvent ev = decode_input('\t');
    TEST_ASSERT_EQUAL(INPUT_MENU, ev.type);
}

void test_decodeinput_creates_IllegalInput_from_invalid_input()
{
    InputEvent ev = decode_input('\a');
    TEST_ASSERT_EQUAL(INPUT_ILLEGAL, ev.type);
}

int main()
{
    RUN_TEST(test_decode_input_creates_MenuInput_from_valid_menu_input);
    RUN_TEST(test_decode_input_creates_TypingTestInput_from_valid_char);
    RUN_TEST(test_decodeinput_creates_IllegalInput_from_invalid_input);
}