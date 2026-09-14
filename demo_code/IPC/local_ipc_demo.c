#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_NAME "/tmp/ipc_fifo_demo"

struct message {
    long type;
    char text[100];
};

void signal_handler(int sig)
{
    printf("[Child] Signal SIGUSR1 received.\n");
}

int main()
{
    int pipe_fd[2];
    pid_t pid;

    printf("=== Local IPC Demo ===\n\n");

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
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
        char buffer[100];

        signal(SIGUSR1, signal_handler);

        printf("[Child] PID = %d\n", getpid());
        printf("[Child] Waiting for signal...\n");

        pause();

        close(pipe_fd[1]);
        read(pipe_fd[0], buffer, sizeof(buffer));
        printf("[Child] Pipe received: %s\n", buffer);
        close(pipe_fd[0]);

        int fifo_fd = open(FIFO_NAME, O_RDONLY);
        if (fifo_fd == -1)
        {
            perror("open FIFO");
            exit(EXIT_FAILURE);
        }

        read(fifo_fd, buffer, sizeof(buffer));
        printf("[Child] FIFO received: %s\n", buffer);
        close(fifo_fd);

        key_t key = ftok(".", 'M');
        int msgid = msgget(key, 0666);

        if (msgid == -1)
        {
            perror("msgget");
            exit(EXIT_FAILURE);
        }

        struct message msg;
        msgrcv(msgid, &msg, sizeof(msg.text), 1, 0);

        printf("[Child] Message Queue received: %s\n", msg.text);

        msgctl(msgid, IPC_RMID, NULL);
        printf("[Child] Local IPC demo completed.\n");
        exit(EXIT_SUCCESS);
    }
    else
    {
        char message[] = "Hello through Pipe";

        sleep(1);
        printf("[Parent] Sending SIGUSR1...\n");
        kill(pid, SIGUSR1);

        close(pipe_fd[0]);
        write(pipe_fd[1], message, strlen(message) + 1);
        close(pipe_fd[1]);

        if (mkfifo(FIFO_NAME, 0666) == -1)
        {
            /* FIFO may already exist */
        }

        int fifo_fd = open(FIFO_NAME, O_WRONLY);
        if (fifo_fd == -1)
        {
            perror("open FIFO");
            exit(EXIT_FAILURE);
        }

        char fifo_message[] = "Hello through FIFO";
        write(fifo_fd, fifo_message, strlen(fifo_message) + 1);
        close(fifo_fd);

        key_t key = ftok(".", 'M');
        int msgid = msgget(key, 0666 | IPC_CREAT);

        if (msgid == -1)
        {
            perror("msgget");
            exit(EXIT_FAILURE);
        }

        struct message msg;
        msg.type = 1;
        strcpy(msg.text, "Hello through Message Queue");

        msgsnd(msgid, &msg, sizeof(msg.text), 0);

        wait(NULL);
        unlink(FIFO_NAME);

        printf("[Parent] Local IPC demo completed.\n");
    }

    return 0;
}
