#ifndef QUOTES_API_H
#define QUOTES_API_H

#include <stdbool.h>

typedef struct  {
    pthread_mutex_t mutex;

    // these need to be protected with mutex
    bool success;
    char* quote;
    char* author;

    // use without mutex lock
    int millis_spent_fetching;
} FetchedQuote;

bool init_quote_api();
void *fetch_quote_thread(void *arg);
void cleanup_quote_api(void);

#endif