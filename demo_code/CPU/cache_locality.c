#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define SIZE 100000000

int array[SIZE];
uint32_t index_array[SIZE];

double get_time()
{
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    return ts.tv_sec + ts.tv_nsec / 1e9;
}

long long sequential_access()
{
    long long sum = 0;

    for(long long i = 0; i < SIZE; i++)
        sum += array[i];

    return sum;
}

long long pseudo_random_access()
{
    long long sum = 0;

    for(long long i = 0; i < SIZE; i++)
        sum += array[index_array[i]];

    return sum;
}

int main()
{
    /* Initialize data and pseudo-random access pattern */
    for(long long i = 0; i < SIZE; i++)
    {
        array[i] = 1;
        index_array[i] = (uint32_t)((i * 7919) % SIZE);
    }

    double start, end;
    long long sequential_sum;
    long long random_sum;

    /* Sequential Access */
    start = get_time();

    sequential_sum = sequential_access();

    end = get_time();

    printf("Sequential sum: %lld\n", sequential_sum);
    printf("Sequential time: %.6f seconds\n\n",
           end - start);

    /* Pseudo-Random Access */
    start = get_time();

    random_sum = pseudo_random_access();

    end = get_time();

    printf("Pseudo-random sum: %lld\n", random_sum);
    printf("Pseudo-random time: %.6f seconds\n",
           end - start);

    return 0;
}
