#include "unity.h"
#include "app.h"
#include "ui.h"

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

    app_handle_key(&s, 'j');

    TEST_ASSERT_EQUAL(1, s.selected);
}