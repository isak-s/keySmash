#ifndef UI_COMMANDS_H
#define UI_COMMANDS_H

#include <ncurses.h>

typedef struct DrawCommand DrawCommand;

typedef void (*DrawCharacterFn)(DrawCommand* self, WINDOW* win);

struct DrawCommand {
    DrawCharacterFn execute;
    char c;
};

DrawCommand new_delete_char_command();

DrawCommand new_draw_char_command(char c);

#endif