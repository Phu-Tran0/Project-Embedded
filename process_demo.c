#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    printf("Main process PID: %d\n", getpid());

    pid = fork();

    if(pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }
    else if(pid == 0)
    {
        printf("Child Process\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
    }
    else
    {
        printf("Parent Process\n");
        printf("Parent PID: %d\n", getpid());

        wait(NULL);

        printf("Child process finished\n");
    }

    return 0;
}
