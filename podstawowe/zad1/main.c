#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

int main()
{
    int sleep_time = 250;
    uint64_t i = 0;
    struct timespec req = {0};
    req.tv_nsec = sleep_time * 1000000L;

    while (true)
    {
        ++i;
        nanosleep(&req, (struct timespec *)NULL);
    }
}