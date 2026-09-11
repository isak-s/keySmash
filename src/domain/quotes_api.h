#ifndef QUOTES_API_H
#define QUOTES_API_H

#include <stdbool.h>
#include <pthread.h>

typedef struct  {
    pthread_mutex_t mutex;

    // these need to be protected with mutex
    bool success;
    char* quote;
    char* author;

    // use without mutex lock
    int millis_spent_fetching;
} FetchedQuote;

void *fetch_quote_thread(void *arg);
void cleanup_quote_api(void);

#endif