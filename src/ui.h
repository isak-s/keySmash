#ifndef UI_H
#define UI_H

typedef enum
{
    UI_KEY_UP,
    UI_KEY_DOWN,
    UI_KEY_QUIT,
    UI_KEY_UNKNOWN

} UiKey;

typedef struct {
  int x;
  int y;
} ScreenPos;

void ui_init_screen_pos(ScreenPos* pos);

void ui_set_screen_pos(ScreenPos* pos, int x, int y);

// void ui_draw_word(const char* word, ScreenPos pos);

void ui_init(void);
void ui_shutdown(void);

UiKey ui_get_key(void);

void ui_clear(void);

void ui_draw_text(const ScreenPos* pos, const char* text);
void ui_refresh(void);

void ui_get_size(int* w, int* h);

#endif