#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>

int main()
{
    printf("=== Shared IPC Demo ===\n\n");

    key_t key = ftok(".", 'S');
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    if (shmid == -1)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    char *shared_data = (char *)shmat(shmid, NULL, 0);

    if (shared_data == (char *)-1)
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        sleep(1);
        printf("[Child] Shared Memory received: %s\n", shared_data);
        shmdt(shared_data);
        exit(EXIT_SUCCESS);
    }
    else
    {
        strcpy(shared_data, "Hello through Shared Memory");
        printf("[Parent] Data written to Shared Memory.\n");

        wait(NULL);
        shmdt(shared_data);
        shmctl(shmid, IPC_RMID, NULL);
    }

    char *mapped_data = mmap(
        NULL, 1024,
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS,
        -1, 0
    );

    if (mapped_data == MAP_FAILED)
    {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        sleep(1);
        printf("[Child] mmap received: %s\n", mapped_data);
        munmap(mapped_data, 1024);
        exit(EXIT_SUCCESS);
    }
    else
    {
        strcpy(mapped_data, "Hello through mmap");
        printf("[Parent] Data written using mmap.\n");

        wait(NULL);
        munmap(mapped_data, 1024);
    }

    printf("[Main] Shared IPC demo completed.\n");
    return 0;
}
