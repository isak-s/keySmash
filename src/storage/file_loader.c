#include "file_loader.h"
#include <stdio.h>
#include <string.h>

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