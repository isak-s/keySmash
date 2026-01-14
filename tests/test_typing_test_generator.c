#include <unity.h>

#include "domain/typing_test.h"

#include <stdlib.h>

void setUp(void) {}    // runs before each test
void tearDown(void) {} // runs after each test


void test_load_words_runs_without_error()
{

    char* words[200];
    for (int i = 0; i < 200; i++) {
        words[i] = malloc(20);
    }
    int loaded = load_words("wordsets/english200.txt", words, 200, 20);

    TEST_ASSERT_EQUAL(loaded, 0);
}

void test_load_words_loads_correct_words()
{
    char* words[200];
    for (int i = 0; i < 200; i++) {
        words[i] = malloc(20);
    }
    int loaded = load_words("wordsets/english200.txt", words, 200, 20);
    TEST_ASSERT_EQUAL(loaded, 0);

    load_words("wordsets/english200.txt", words, 200, 20);

    TEST_ASSERT_EQUAL_STRING("the", words[0]);
    TEST_ASSERT_EQUAL_STRING("also", words[80]);
    TEST_ASSERT_EQUAL_STRING("perchance", words[199]);
}

int main()
{
    RUN_TEST(test_load_words_runs_without_error);
    RUN_TEST(test_load_words_loads_correct_words);
}