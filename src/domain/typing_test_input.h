#ifndef TYPING_TEST_INPUT_H
#define TYPING_TEST_INPUT_H

#include <stdbool.h>
#include <stdint.h>

typedef struct TypingTestInput {
    bool is_correct;
    bool is_backspace;
    int64_t time_since_test_start;
    // has to be an int since there are other non-alphabetic keycodes.
    int inputted;
} TypingTestInput;

#endif