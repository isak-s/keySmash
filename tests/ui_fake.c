#include "ui.h"

static UiKey scripted_keys[32];
static int key_count;
static int key_index;

static int fake_width = 80;
static int fake_height = 24;

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

void ui_set_screen_pos(ScreenPos* pos, int x, int y)
{
    pos->x = x;
    pos->y = y;
}

void ui_get_size(int* w, int* h)
{
    *w = fake_width;
    *h = fake_height;
}

void ui_fake_resize(int w, int h) {
    fake_width = w;
    fake_height = h;
}
