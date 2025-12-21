#include "ui.h"
#include "app.h"

#define DELAY 35000

int main(int argc, char *argv[])
{
  (void)argc;
  (void)argv;

  Appstate s;
  ScreenPos pos;

  app_init(&s);
  ui_init();

  ui_set_screen_pos(&pos, 0, 0);

  while (s.running) {
    ui_clear();
    ui_draw_text(&pos, "Hello curses");
    ui_refresh();

    UiKey key = ui_get_key();
    app_handle_key(&s, key);
  }

  ui_shutdown();

  return 0;
}
