#include "unity.h"
#include "app.h"

void test_quit_key_stops_app(void)
{
    Appstate s;
    app_init(&s);

    app_handle_key(&s, 'q');

    TEST_ASSERT_FALSE(s.running);
}

void test_down_key_moves_selection(void)
{
    Appstate s;
    app_init(&s);

    app_handle_key(&s, 'j');

    TEST_ASSERT_EQUAL(1, s.selected);
}