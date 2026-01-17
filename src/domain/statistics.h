#ifndef STATISTICS_H
#define STATISTICS_H

#include "typing_test_input.h"

typedef struct
{
    int nbr_correct;
    int nbr_incorrect;
    int wpm;
    char currword[32];
} Statistics;

Statistics statistics_create();

void statistics_update(Statistics* stat, TypingTestInput* inp);

void statistics_reset(Statistics* stat);

#endif