#include "ui.h"

static UiKey scripted_keys[32];
static int key_count;
static int key_index;

void ui_fake_feed_keys(const UiKey* keys, int count)
{
    for (int i = 0; i < count; i++) {
        scripted_keys[i] = keys[i];
    }
    key_count += count;
    key_index = 0;
}

UiKey ui_get_key(void)
{
    if (key_index < key_count)
    {
        return scripted_keys[key_index++];
    }
    return UI_KEY_QUIT;
}

void ui_init(void) {}
void ui_shutdown(void) {}

void ui_clear(void) {}
void ui_draw_text(const ScreenPos* pos, const char* text) {
    (void)pos;
    (void)text;
}
void ui_refresh(void) {}
