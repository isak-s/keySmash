#ifndef TYPING_TEST_MODE_H
#define TYPING_TEST_MODE_H
typedef enum {
    ENGLISH_200_15_S,
    ENGLISH_200_60_S,
    ENGLISH_1000_15_S,
    ENGLISH_1000_60_S,
    //ENGLISH_QUOTE,
    //SWEDISH_200,

    TYPING_TEST_MODE_COUNT
} TypingTestMode;

extern const char* typing_test_mode_names[TYPING_TEST_MODE_COUNT];

#endif