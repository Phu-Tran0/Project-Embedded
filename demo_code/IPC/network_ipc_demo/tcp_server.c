#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[1024] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 1);

    printf("[TCP Server] Waiting for client...\n");

    client_fd = accept(server_fd,
        (struct sockaddr *)&address, &addrlen);

    recv(client_fd, buffer, sizeof(buffer), 0);
    printf("[TCP Server] Received: %s\n", buffer);

    send(client_fd, "Hello from TCP Server",
         strlen("Hello from TCP Server") + 1, 0);

    close(client_fd);
    close(server_fd);
    return 0;
}
