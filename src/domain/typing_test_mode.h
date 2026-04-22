#ifndef TYPING_TEST_MODE_H
#define TYPING_TEST_MODE_H
typedef enum {
    ENGLISH_200,
    ENGLISH_1000,
    //ENGLISH_QUOTE,
    //SWEDISH_200,

    TYPING_TEST_MODE_COUNT
} TypingTestMode;

extern const char* typing_test_mode_names[TYPING_TEST_MODE_COUNT];

#endif