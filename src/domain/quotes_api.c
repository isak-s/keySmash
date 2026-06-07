#include "quotes_api.h"

typedef struct {
  char *memory;
  size_t size;
} MemoryStruct;

size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t realsize = size * nmemb;
  MemoryStruct *mem = (MemoryStruct *)userp;

  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if(ptr == NULL) {
      printf("error: not enough memory when fetching quote\n");
      return 0;
  }

  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

const char url[] = "https://thequoteshub.com/api/default/get_api_random_quote";

void init_curl() {
    CURL *curl_handle;
    MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_handle = curl_easy_init();
    if (curl_handle) {
        curl_easy_setopt(curl_handle, CURLOPT_URL, url);
        curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    }
}

// uses random quotes from thequoteshub
char* get_quote(CURL* curl_handle, MemoryStruct chunk) {

    CURLcode res;
    char* quote;

    res = curl_easy_perform(curl_handle);

    if (res != CURLE_OK)
    {
        fprintf(stderr, "No connection to api. Quote fetching error %s\n", curl_easy_strerror(res));
        // error handling here!
    }
    else
    {
        printf("Size: %lu \n", (unsigned long)chunk.size);
        printf("Data: %s\n", chunk.memory);

        char *text_start = strstr(chunk.memory, "\"text\":\"");
        if (text_start)
        {
            text_start += strlen("\"text\":\"");

            char *text_end = strstr(text_start, "\",\"author\"");
            if (text_end)
            {
                size_t len = text_end - text_start;

                memcpy(quote, text_start, len);
                quote[len] = '\0';

                printf("Quote: %s\n", quote);
            }
        }

        curl_easy_cleanup(curl_handle);
        free(chunk.memory);
    }
    return quote;
}


int main(int argc, char* argv[]) {


    CURL *curl_handle;
    CURLcode res;
    MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_handle = curl_easy_init();
    if (curl_handle) {
        curl_easy_setopt(curl_handle, CURLOPT_URL, url);
        curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        res = curl_easy_perform(curl_handle);

        if (res != CURLE_OK) {
            fprintf(stderr, "No connection to api. Quote fetching error %s\n", curl_easy_strerror(res));
            // error handling here!
        } else {
            printf("Size: %lu \n", (unsigned long) chunk.size);
            printf("Data: %s\n", chunk.memory);

            char *text_start = strstr(chunk.memory, "\"text\":\"");
            if (text_start)
            {
                text_start += strlen("\"text\":\"");

                char *text_end = strstr(text_start, "\",\"author\"");
                if (text_end)
                {
                    size_t len = text_end - text_start;

                    char *quote = malloc(len + 1);
                    memcpy(quote, text_start, len);
                    quote[len] = '\0';

                    printf("Quote: %s\n", quote);
                    free(quote);
                }
            }

            curl_easy_cleanup(curl_handle);
            free(chunk.memory);
        }
    }
    return 0;
}