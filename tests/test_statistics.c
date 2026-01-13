#include <unity.h>
#include "domain/statistics.h"
#include "domain/clock_helper.h"

static Statistics stat;

void setUp(void) {
    stat = statistics_create();
}    // runs before each test
void tearDown(void) {} // runs after each test

void test_create_statistics()
{
    TEST_ASSERT_EQUAL(0, stat.nbr_correct);
    TEST_ASSERT_EQUAL(0, stat.nbr_incorrect);
    TEST_ASSERT_EQUAL(0, stat.wpm);
}

void test_update_statistics_updates_correct_count_if_correct_input()
{
    TypingTestInput inp = {.inputted = 'a', .is_correct = true, .time_since_test_start = 1};
    statistics_update(&stat, &inp);

    TEST_ASSERT_EQUAL(1, stat.nbr_correct);
    TEST_ASSERT_EQUAL(0, stat.nbr_incorrect);
}

void test_update_statistics_updates_incorrect_count_if_incorrect_input()
{
    TypingTestInput inp = {.inputted = 'a', .is_correct = false, .time_since_test_start = 1};
    statistics_update(&stat, &inp);

    TEST_ASSERT_EQUAL(0, stat.nbr_correct);
    TEST_ASSERT_EQUAL(1, stat.nbr_incorrect);
}

void test_update_statistics_updates_wpm_single_char()
{
    TypingTestInput inp = {.inputted = 'a', .is_correct = true, .time_since_test_start = 1000};
    statistics_update(&stat, &inp);

    TEST_ASSERT_EQUAL(1, stat.nbr_correct);
    TEST_ASSERT_EQUAL(0, stat.nbr_incorrect);
    TEST_ASSERT_EQUAL(12, stat.wpm);
}

// five chars counts as 1 word
void test_update_statistics_updates_wpm_single_word()
{
    for (int i = 0; i < 5; i++) { // last input happens 1 second into test
        TypingTestInput inp = {.inputted = 'a', .is_correct = true, .time_since_test_start = 996 + i};
        statistics_update(&stat, &inp);
    }
    TEST_ASSERT_EQUAL(5, stat.nbr_correct);
    TEST_ASSERT_EQUAL(0, stat.nbr_incorrect);
    TEST_ASSERT_EQUAL(60, stat.wpm);
}

void test_update_statistics_tracks_whitespaces()
{
    for (int i = 0; i < 5; i++) { // last input happens 1 second into test
        TypingTestInput inp = {.inputted = ' ', .is_correct = true, .time_since_test_start = 996 + i};
        statistics_update(&stat, &inp);
    }
    TEST_ASSERT_EQUAL(5, stat.nbr_correct);
    TEST_ASSERT_EQUAL(0, stat.nbr_incorrect);
    TEST_ASSERT_EQUAL(60, stat.wpm);
}

int main()
{
    RUN_TEST(test_create_statistics);
    RUN_TEST(test_update_statistics_updates_correct_count_if_correct_input);
    RUN_TEST(test_update_statistics_updates_incorrect_count_if_incorrect_input);
    RUN_TEST(test_update_statistics_updates_wpm_single_char);
    RUN_TEST(test_update_statistics_updates_wpm_single_word);
    RUN_TEST(test_update_statistics_tracks_whitespaces);
}