// ONLY ONE THREAD!!!!!!!

#include "quotes_api.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <curl/curl.h>

#include <pthread.h>


typedef struct {
    char *memory;
    size_t size;
} MemoryStruct;

static CURL *curl_handle = NULL;

static MemoryStruct chunk = {
    .memory = NULL,
    .size = 0
};

static const char url[] =
    "https://thequoteshub.com/api/default/get_api_random_quote";


/*
 * Called by libcurl whenever data is received.
 */
static size_t WriteMemoryCallback(
    void *contents,
    size_t size,
    size_t nmemb,
    void *userp
)
{
    size_t realsize = size * nmemb;

    MemoryStruct *mem = userp;

    char *ptr = realloc(
        mem->memory,
        mem->size + realsize + 1
    );

    if (ptr == NULL) {
        fprintf(
            stderr,
            "Error: not enough memory when fetching quote\n"
        );

        return 0;
    }

    mem->memory = ptr;

    memcpy(
        mem->memory + mem->size,
        contents,
        realsize
    );

    mem->size += realsize;

    mem->memory[mem->size] = '\0';

    return realsize;
}

static CURL *init_curl(MemoryStruct *chunk)
{
    CURL *handle = curl_easy_init();

    if (handle == NULL) {
        return NULL;
    }

    CURLcode result;

    result = curl_easy_setopt(
        handle,
        CURLOPT_URL,
        url
    );

    if (result != CURLE_OK) {
        curl_easy_cleanup(handle);
        return NULL;
    }

    result = curl_easy_setopt(
        handle,
        CURLOPT_FOLLOWLOCATION,
        1L
    );

    if (result != CURLE_OK) {
        curl_easy_cleanup(handle);
        return NULL;
    }

    result = curl_easy_setopt(
        handle,
        CURLOPT_WRITEFUNCTION,
        WriteMemoryCallback
    );

    if (result != CURLE_OK) {
        curl_easy_cleanup(handle);
        return NULL;
    }

    result = curl_easy_setopt(
        handle,
        CURLOPT_WRITEDATA,
        chunk
    );

    if (result != CURLE_OK) {
        curl_easy_cleanup(handle);
        return NULL;
    }

    result = curl_easy_setopt(
        handle,
        CURLOPT_USERAGENT,
        "libcurl-agent/1.0"
    );

    if (result != CURLE_OK) {
        curl_easy_cleanup(handle);
        return NULL;
    }

    return handle;
}

static bool init_quote_api(void)
{
    if (curl_handle != NULL) {
        return true;
    }

    /*
     * curl_global_init() should be called before using libcurl.
     */
    CURLcode result = curl_global_init(CURL_GLOBAL_DEFAULT);

    if (result != CURLE_OK) {
        fprintf(
            stderr,
            "Failed to initialize libcurl\n"
        );

        return false;
    }


    /*
     * Allocate the initial response buffer.
     */
    chunk.memory = malloc(1);

    if (chunk.memory == NULL) {
        fprintf(
            stderr,
            "Failed to allocate memory\n"
        );

        curl_global_cleanup();

        return false;
    }

    chunk.memory[0] = '\0';
    chunk.size = 0;


    /*
     * Create and configure the CURL handle.
     */
    curl_handle = init_curl(&chunk);

    if (curl_handle == NULL) {
        fprintf(
            stderr,
            "Failed to initialize CURL handle\n"
        );

        free(chunk.memory);

        chunk.memory = NULL;
        chunk.size = 0;

        curl_global_cleanup();

        return false;
    }

    return true;
}


/*
 * Clean up everything owned by this module.
 *
 * Must be called when the program is finished using the API.
 */
void cleanup_quote_api(void)
{
    if (curl_handle != NULL) {
        curl_easy_cleanup(curl_handle);
        curl_handle = NULL;
    }

    free(chunk.memory);

    chunk.memory = NULL;
    chunk.size = 0;

    curl_global_cleanup();
}


/*
 * Fetch and parse one quote.
 *
 * The returned string belongs to the caller.
 *
 * Caller is responsible for:
 *
 *     free(quote);
 */
static char *get_quote(void)
{
    if (curl_handle == NULL) {
        fprintf(
            stderr,
            "Error: CURL has not been initialized\n"
        );

        return NULL;
    }

    chunk.size = 0;

    if (chunk.memory != NULL) {
        chunk.memory[0] = '\0';
    }


    CURLcode result = curl_easy_perform(curl_handle);

    if (result != CURLE_OK) {
        fprintf(
            stderr,
            "No connection to API. "
            "Quote fetching error: %s\n",
            curl_easy_strerror(result)
        );

        return NULL;
    }


    // printf(
        // "Size: %lu\n",
        // (unsigned long)chunk.size
    // );

    // printf(
        // "Data: %s\n",
        // chunk.memory
    // );

    char *text_start = strstr(
        chunk.memory,
        "\"text\":\""
    );

    if (text_start == NULL) {
        fprintf(
            stderr,
            "Could not find quote text in API response\n"
        );

        return NULL;
    }


    text_start += strlen("\"text\":\"");

    char *text_end = strstr(
        text_start,
        "\",\"author\""
    );

    if (text_end == NULL) {
        fprintf(
            stderr,
            "Could not find end of quote in API response\n"
        );

        return NULL;
    }


    size_t len = text_end - text_start;

    char *quote = malloc(len + 1);

    if (quote == NULL) {
        fprintf(
            stderr,
            "Failed to allocate memory for quote\n"
        );

        return NULL;
    }


    memcpy(
        quote,
        text_start,
        len
    );

    quote[len] = '\0';


    // printf(
        // "Quote: %s\n",
        // quote
    // );


    return quote;
}

char *fetch_quote(void)
{
    /*
     * Lazily initialize the API if necessary.
     */
    if (curl_handle == NULL) {
        if (!init_quote_api()) {
            return NULL;
        }
    }

    return get_quote();
}


// Thread entry point.
// takes the FetchedQuote shared struct and puts stuff in it,
    // respecting the mutex lock.
void *fetch_quote_thread(void* arg)
{
    FetchedQuote *fetched_quote = (FetchedQuote*) arg;

    pthread_mutex_lock(&fetched_quote->mutex);
    fetched_quote->success = false;
    fetched_quote->quote = "Fetching quote";
    fetched_quote->author = "Isak Simonsson";
    pthread_mutex_unlock(&fetched_quote->mutex);

    // ignore millisfetched for now.
    char *quote = fetch_quote();

    if (quote != NULL) {

        /*
         * TODO:
         *
         * Publish the quote to your shared FetchedQuote struct here.
         *
         * For example:
         *
         * fetched_quote->quote = quote;
         * fetched_quote->success = true;
         *
         * Those operations will eventually need your mutex.
         */
        pthread_mutex_lock(&fetched_quote->mutex);
        fetched_quote->quote = quote;
        fetched_quote->success = true;
        pthread_mutex_unlock(&fetched_quote->mutex);

        //free(quote);
    }

    return NULL;
}


int main(void)
{

    FetchedQuote fetched_quote = {
        .mutex = PTHREAD_MUTEX_INITIALIZER,
        .success = false,
        .quote = "fetching quote",
        .author = "No author",
        .millis_spent_fetching = 0,
    };

    pthread_t thread;

    pthread_create(
        &thread,
        NULL,
        fetch_quote_thread,
        &fetched_quote
    );

    pthread_join(thread, NULL);

    //pthread_mutex_lock(&fetched_quote.mutex);
    printf(
        "Fetched quote: %s\n",
        fetched_quote.quote);
    //pthread_mutex_unlock(&fetched_quote.mutex);
    /*
     * Clean up once, at the very end.
     */
    cleanup_quote_api();

    return EXIT_SUCCESS;
}
