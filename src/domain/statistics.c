#include "statistics.h"
// words per minute = (correct_chars / 5) / minutes
// minutes = ms / 60000
void update_wpm(Statistics* stat, TypingTestInput* inp)
{
    stat->wpm = (stat->nbr_correct * 60000)
              / (inp->time_since_test_start * 5);
}

Statistics statistics_create()
{
    return (Statistics) { .nbr_correct = 0, .nbr_incorrect = 0, .wpm = 0, .currword = ""};
}

void statistics_update(Statistics* stat, TypingTestInput* inp)
{
    stat->nbr_correct += inp->is_correct;
    stat->nbr_incorrect += !inp->is_correct;
    update_wpm(stat, inp);
}

void statistics_reset(Statistics* stat)
{
    stat->nbr_correct = 0;
    stat->nbr_incorrect = 0;
    stat->wpm = 0;
}