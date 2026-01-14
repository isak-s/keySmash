#ifndef TYPING_TEST_GENERATOR_H
#define TYPING_TEST_GENERATOR_

#include "typing_test.h"

typedef struct {
    char* word_buffer;
    int capacity;
    char** wordset;
} TypingTestGenerator;

int load_words(const char* path, char** words, int max_count, int max_word_len);

#endif