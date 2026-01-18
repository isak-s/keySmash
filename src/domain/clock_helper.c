#define _POSIX_C_SOURCE 200809L
#include "clock_helper.h"

#include <stdint.h>

#if defined(_WIN32)

#include <windows.h>

int64_t now_ms(void)
{
    static LARGE_INTEGER freq;
    static int initialized = 0;

    if (!initialized) {
        QueryPerformanceFrequency(&freq);
        initialized = 1;
    }

    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);

    return (counter.QuadPart * 1000LL) / freq.QuadPart;
}

#else   // POSIX

#include <time.h>
#include <stdint.h>

int64_t now_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (int64_t)ts.tv_sec * 1000LL + ts.tv_nsec / 1000000LL;
}

void sleep_ms(long ms)
{
    struct timespec ts;
    ts.tv_sec  = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000L;
    nanosleep(&ts, NULL);
}

#endif