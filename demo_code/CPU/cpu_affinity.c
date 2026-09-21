#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>
#include <time.h>

#define NUM_THREADS 4
#define SIZE 100000000

long long data[SIZE];

typedef struct {
    int id;
    long long start;
    long long end;
} ThreadArgs;


void* sum_array(void* arg)
{
    ThreadArgs* args = (ThreadArgs*)arg;

    cpu_set_t cpuset;

    CPU_ZERO(&cpuset);
    CPU_SET(args->id % sysconf(_SC_NPROCESSORS_ONLN), &cpuset);

    pthread_setaffinity_np(
        pthread_self(),
        sizeof(cpu_set_t),
        &cpuset
    );


    long long sum = 0;

    for(long long i = args->start; i < args->end; i++)
    {
        sum += data[i];
    }


    printf(
        "Thread %d running on CPU %d, partial sum = %lld\n",
        args->id,
        sched_getcpu(),
        sum
    );


    return NULL;
}


double get_time()
{
    struct timespec ts;

    clock_gettime(
        CLOCK_MONOTONIC,
        &ts
    );

    return ts.tv_sec + ts.tv_nsec / 1e9;
}


int main()
{
    printf(
        "Available CPU cores: %ld\n",
        sysconf(_SC_NPROCESSORS_ONLN)
    );


    for(long long i = 0; i < SIZE; i++)
        data[i] = 1;



    pthread_t threads[NUM_THREADS];
    ThreadArgs args[NUM_THREADS];


    double start = get_time();


    for(int i = 0; i < NUM_THREADS; i++)
    {
        args[i].id = i;
        args[i].start = i * (SIZE / NUM_THREADS);
        args[i].end = (i+1)*(SIZE / NUM_THREADS);


        pthread_create(
            &threads[i],
            NULL,
            sum_array,
            &args[i]
        );
    }


    for(int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(
            threads[i],
            NULL
        );
    }


    double end = get_time();


    printf("\nExecution time: %.6f seconds\n",
            end-start);


    return 0;
}
