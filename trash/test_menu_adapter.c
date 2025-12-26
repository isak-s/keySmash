#include "unity.h"
#include "menu_adapter.h"

void setUp(void) {}
void tearDown(void) {}

void test_ui_menu_create()
{
    //Menu menu;
    TEST_ASSERT_TRUE(false);
}
// UIElement ui_menu_create(Menu *menu, ScreenPos pos)

void test_ui_label_create()
{
    // Label label;
    TEST_ASSERT_TRUE(false);
}
// UIElement ui_label_create(Label* label, ScreenPos pos)

int main()
{
    RUN_TEST(test_ui_label_create);
    RUN_TEST(test_ui_menu_create);
}