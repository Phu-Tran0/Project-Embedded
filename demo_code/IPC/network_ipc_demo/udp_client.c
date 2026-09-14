#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081

int main()
{
    int sock;
    struct sockaddr_in server;
    socklen_t len = sizeof(server);
    char buffer[1024] = {0};

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    sendto(sock, "Hello from UDP Client",
           strlen("Hello from UDP Client") + 1, 0,
           (struct sockaddr *)&server, sizeof(server));

    recvfrom(sock, buffer, sizeof(buffer), 0,
             (struct sockaddr *)&server, &len);

    printf("[UDP Client] Received: %s\n", buffer);

    close(sock);
    return 0;
}
