#ifndef INPUT_DECODER_H
#define INPUT_DECODER_H

#include "domain/typing_test_input.h"
#include "menu_input.h"
#include <stdbool.h>

typedef enum {
    INPUT_TYPING,
    INPUT_MENU,
    INPUT_NONE,
    INPUT_ILLEGAL
} InputEventType;

typedef struct {
    int error_code;
} IllegalInput;

typedef struct {
    InputEventType type;
    union {
        TypingTestInput typing;
        MenuInput menu;
        IllegalInput illegal;
    };
} InputEvent;

InputEvent get_input();

#endif