#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main()
{
    int sock;
    struct sockaddr_in server;
    char buffer[1024] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    connect(sock, (struct sockaddr *)&server, sizeof(server));

    send(sock, "Hello from TCP Client",
         strlen("Hello from TCP Client") + 1, 0);

    recv(sock, buffer, sizeof(buffer), 0);
    printf("[TCP Client] Received: %s\n", buffer);

    close(sock);
    return 0;
}
