#include "unity.h"
#include "app.h"
#include "ui.h"
#include "ui_fake.h"

void setUp(void) {}    // runs before each test
void tearDown(void) {} // runs after each test

void test_quit_key_stops_app(void)
{
    Appstate s;
    app_init(&s);

    app_handle_key(&s, UI_KEY_QUIT);

    TEST_ASSERT_FALSE(s.running);
}

void test_down_key_moves_selection(void)
{
    Appstate s;
    app_init(&s);

    app_handle_key(&s, UI_KEY_DOWN);

    TEST_ASSERT_EQUAL(1, s.selected);
}

void test_up_key_moves_selection(void)
{
    Appstate s;
    app_init(&s);

    app_handle_key(&s, UI_KEY_UP);

    TEST_ASSERT_EQUAL(-1, s.selected);
}

void test_resize_repositions_ui(void)
{
    Appstate s;
    Screen scr;

    ui_fake_resize(40, 10);

    // on_app_screen_resized(&s, &scr);

    TEST_ASSERT_EQUAL_INT32(40, s.window_width);
    TEST_ASSERT_EQUAL_INT32(10, s.window_height);
}

int main() {
    RUN_TEST(test_quit_key_stops_app);
    RUN_TEST(test_down_key_moves_selection);
    RUN_TEST(test_up_key_moves_selection);
    RUN_TEST(test_resize_repositions_ui);
}