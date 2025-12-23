#ifndef APP_H
#define APP_H

typedef struct {
    int selected;
    int running;
    int window_height;
    int window_width;
} Appstate;

void app_init(Appstate* s);
void app_handle_key(Appstate* s, int key);

void on_app_screen_resized(Appstate* s);

#endif