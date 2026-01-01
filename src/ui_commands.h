#ifndef UI_COMMANDS_H
#define UI_COMMANDS_H

#include <ncurses.h>
#include "typing_test_input.h"
#include "render_context.h"

typedef struct DrawCommand DrawCommand;

typedef void (*DrawCharacterFn)(DrawCommand* self, RenderContext* win);

struct DrawCommand {
    DrawCharacterFn execute;
    char c;
};

DrawCommand new_delete_char_command();

DrawCommand new_draw_char_command(char c);

DrawCommand draw_command_from_input(TypingTestInput* inp);

#endif