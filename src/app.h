#ifndef APP_H
#define APP_H

typedef struct {
    int selected;
    int running;
} Appstate;

void app_init(Appstate* s);
void app_handle_key(Appstate* s, int key);

#endif