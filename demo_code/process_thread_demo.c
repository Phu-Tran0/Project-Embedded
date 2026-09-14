#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

void* thread_function(void* arg)
{
    printf("[Thread] Child thread (TID: %lu) is running...\n",
           pthread_self());

    sleep(1);

    printf("[Thread] Child thread finished.\n");

    pthread_exit(NULL);
}

int main()
{
    pthread_t my_thread;
    pid_t pid;

    // 1. Create a thread
    printf("[Main] 1. Creating thread using pthread_create()...\n");

    if (pthread_create(&my_thread, NULL, thread_function, NULL) != 0)
    {
        perror("Thread creation error");
        exit(EXIT_FAILURE);
    }

    // 2. Wait for the thread
    printf("[Main] 2. Waiting for thread using pthread_join()...\n");

    if (pthread_join(my_thread, NULL) != 0)
    {
        perror("Thread join error");
        exit(EXIT_FAILURE);
    }

    printf("[Main] Thread resources cleaned up.\n\n");

    // 3. Create a child process
    printf("[Main] 3. Creating child process using fork()...\n");

    pid = fork();

    if (pid < 0)
    {
        perror("Fork error");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // Child process
        printf("[Child] Child process (PID: %d) is calling exec()...\n",
               getpid());

        // 4. Replace child process with "ls -l"
        char *args[] = {"ls", "-l", NULL};

        execvp("ls", args);

        // Only executed if execvp() fails
        perror("Exec error");
        exit(EXIT_FAILURE);
    }
    else
    {
        // Parent process
        int status;

        printf("[Parent] Parent process (PID: %d) is waiting for child (PID: %d)...\n",
               getpid(), pid);

        // 5. Wait for child process
        wait(&status);

        if (WIFEXITED(status))
        {
            printf("\n[Parent] Child process finished normally. Exit code: %d\n",
                   WEXITSTATUS(status));
        }
    }

    return 0;
}
