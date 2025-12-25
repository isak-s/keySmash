#include "app.h"
#include "ui.h"
#include "stdbool.h"
#include "menu.h"

void app_init(Appstate* s)
{
    s->selected = 0;
    s->running  = 1;
}

void app_handle_key(Appstate* s, int key)
{
    switch (key)
    {
    case UI_KEY_DOWN:
        s->selected++;
        break;
    case UI_KEY_UP:
        s->selected--;
        break;
    case UI_KEY_QUIT:
        s->running = 0;

    default:
        break;
    }
}

bool is_app_screen_resized()
{
    return false;
}

void on_app_screen_resized(Appstate* s)
{
    ui_get_size(&s->window_width, &s->window_height);
}

void screen_draw(const Screen* screen)
{
    for (size_t i = 0; i < screen->count; i++) {
        screen->elements[i].draw(&screen->elements[i]);
    }
}

void screen_resize(const Screen* screen, int w, int h)
{
    for (size_t i = 0; i < screen->count; i++) {
        screen->elements[i].resize(&screen->elements[i], w, h);
    }
}