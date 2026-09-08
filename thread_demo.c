#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function(void *arg)
{
    int id = *(int *)arg;

    printf("Thread %d is running\n", id);

    sleep(1);

    printf("Thread %d finished\n", id);

    return NULL;
}

int main()
{
    pthread_t thread1, thread2;

    int id1 = 1;
    int id2 = 2;

    printf("Main thread started\n");

    pthread_create(&thread1, NULL, thread_function, &id1);
    pthread_create(&thread2, NULL, thread_function, &id2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("All threads finished\n");

    return 0;
}
