#ifndef APP_STATE_H
#define APP_STATE_H

#include "domain/typing_test_mode.h"
#include "ui/colors.h"

typedef enum {
    APP_IN_TEST,
    APP_NEW_TEST,
    APP_STATISTICS,
    APP_QUIT
} AppMode;

typedef struct {
    AppMode mode;
    TypingTestMode typing_test_mode;
    ColorScheme color_scheme;
} Appstate;

#endif