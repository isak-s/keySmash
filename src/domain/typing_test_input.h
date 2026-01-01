#ifndef TYPING_TEST_INPUT_H
#define TYPING_TEST_INPUT_H

typedef struct TypingTestInput {
    bool is_correct;
    int  time_since_test_start;
    // has to be an int since there are other non-alphabetic keycodes.
    int inputted;
} TypingTestInput;

#endif