#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 5

void *Print(void *id)
{
    printf("Hello SCR. Written by thread ID: %ld!\n", (int)id);
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int error_code = 0;
    for (int id = 0; id < NUM_THREADS; id++)
    {
        printf("Creating thread %ld\n", id);
        error_code = pthread_create(&threads[id], NULL, Print, (void *)id);
        if (error_code)
        {
            printf("Return code from pthread_create() is %d\n", error_code);
            exit(error_code);
        }
    }

    pthread_exit(NULL);
}
