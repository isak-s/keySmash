#include "typing_test_generator.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* loads words into an array defined by caller */
/* returns number of words loaded, or -1 on error */
int load_words(const char* path, char** words, int max_count, int max_word_len)
{
    FILE* f = fopen(path, "r");
    if (!f) return -1;

    int count = 0;

    while (count < max_count && fgets(words[count], max_word_len, f)) {
        words[count][strcspn(words[count], "\n")] = '\0';
        count++;
    }

    fclose(f);
    return 0;
}

/*TypingTest*/ void typing_test_new_english_200()
{
    // create a buffer that gets refilled periodically
    // at start prev word is null
    // while word != prev word set word to random word from wordset.
    // add to buffer until we reach capacity
    char* words[200];
    for (int i = 0; i < 200; i++) {
        words[i] = malloc(20);
    }

    load_words("wordsets/english200.txt", words, 200, 20);
    char* prev_word = "null";
    char* curr_word = "null";
    int capacity = 100;
    for (int i = 0; i < capacity; i++)
    {
        while (strcmp(prev_word, curr_word))
        {
            int i = rand() % 199;
            prev_word = curr_word;
            curr_word = words[i];
        }
    }
}