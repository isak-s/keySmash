#include <unity.h>

#include "ui/colors.h"
#include "ui/ui_commands.h"

void setUp(void) {
    initscr();
    start_color();
    use_default_colors();
}    // runs before each test
void tearDown(void) {
    endwin();
} // runs after each test

void test_gruvbox_color_pairs(void)
{
    initscr();
    start_color();
    use_default_colors();

    set_color_scheme(stdscr, GRUVBOX);

    short fg, bg;

    pair_content(COLOR_PRIMARY, &fg, &bg);
    TEST_ASSERT_EQUAL(214, fg);
    TEST_ASSERT_EQUAL(234, bg);

    pair_content(COLOR_CORRECT, &fg, &bg);
    TEST_ASSERT_EQUAL(108, fg);
    TEST_ASSERT_EQUAL(234, bg);

    pair_content(COLOR_INCORRECT, &fg, &bg);
    TEST_ASSERT_EQUAL(COLOR_RED, fg);
    TEST_ASSERT_EQUAL(234, bg);

    endwin();
}

void test_tron_orange_color_pairs(void)
{
    initscr();
    start_color();
    use_default_colors();

    set_color_scheme(stdscr, TRON_ORANGE);

    short fg, bg;

    /* PRIMARY */
    pair_content(COLOR_PRIMARY, &fg, &bg);
    TEST_ASSERT_EQUAL(214, fg);
    TEST_ASSERT_EQUAL(234, bg);

    /* CORRECT */
    pair_content(COLOR_CORRECT, &fg, &bg);
    TEST_ASSERT_EQUAL(222, fg);
    TEST_ASSERT_EQUAL(237, bg);

    /* INCORRECT */
    pair_content(COLOR_INCORRECT, &fg, &bg);
    TEST_ASSERT_EQUAL(COLOR_BLACK, fg);
    TEST_ASSERT_EQUAL(222, bg);

    endwin();
}

void test_background_color_applied(void)
{
    set_color_scheme(stdscr, GRUVBOX);

    chtype bg = getbkgd(stdscr);
    TEST_ASSERT_TRUE(bg & COLOR_PAIR(COLOR_PRIMARY));
}

int main()
{
    RUN_TEST(test_background_color_applied);
    RUN_TEST(test_gruvbox_color_pairs);
    RUN_TEST(test_tron_orange_color_pairs);
}