#include "app.h"

void app_init(Appstate* s)
{
    s->selected = 0;
    s->running  = 1;
}

void app_handle_key(Appstate* s, int key)
{
    switch (key)
    {
    case 'j':
        s->selected++;
        break;
    case 'k':
        s->selected--;
        break;
    case 'q':
        s->running = 0;

    default:
        break;
    }
}