#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000000


int array[SIZE];


double get_time()
{
    struct timespec ts;

    clock_gettime(
        CLOCK_MONOTONIC,
        &ts
    );

    return ts.tv_sec + ts.tv_nsec/1e9;
}



void sequential_access()
{
    long long sum = 0;


    for(long long i = 0; i < SIZE; i++)
    {
        sum += array[i];
    }


    printf(
        "Sequential sum: %lld\n",
        sum
    );
}



void random_access()
{
    long long sum = 0;


    for(long long i = 0; i < SIZE; i++)
    {
        long long index =
            (i * 7919) % SIZE;


        sum += array[index];
    }


    printf(
        "Random sum: %lld\n",
        sum
    );
}



int main()
{

    for(long long i = 0; i < SIZE; i++)
        array[i] = 1;



    double start,end;


    start=get_time();

    sequential_access();

    end=get_time();


    printf(
        "Sequential time: %.6f seconds\n\n",
        end-start
    );



    start=get_time();

    random_access();

    end=get_time();


    printf(
        "Random time: %.6f seconds\n",
        end-start
    );


    return 0;
}
