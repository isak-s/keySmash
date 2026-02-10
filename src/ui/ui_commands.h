// Cursor movement lives in executor by mutating ctx

#ifndef UI_COMMANDS_H
#define UI_COMMANDS_H

#define _XOPEN_SOURCE_EXTENDED 1 // for wide character support. (swedish)
#include <wchar.h>
#include <wctype.h>
#include <ncurses.h>
#include "domain/typing_test_input.h"
#include "render_context.h"

typedef struct DrawCommand DrawCommand;

typedef void (*DrawCharacterFn)(DrawCommand* self, RenderContext* ctx);

struct DrawCommand {
    DrawCharacterFn execute;
    wchar_t c;  // wchar to be compatible with unicode
};

DrawCommand new_delete_char_command();

DrawCommand new_draw_char_command(char c);

DrawCommand draw_command_from_input(const TypingTestInput* inp);

#endif