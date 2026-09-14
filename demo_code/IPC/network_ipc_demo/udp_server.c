#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081

int main()
{
    int sock;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    char buffer[1024] = {0};

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(sock, (struct sockaddr *)&server, sizeof(server));

    printf("[UDP Server] Waiting for datagram...\n");

    recvfrom(sock, buffer, sizeof(buffer), 0,
             (struct sockaddr *)&client, &len);

    printf("[UDP Server] Received: %s\n", buffer);

    sendto(sock, "Hello from UDP Server",
           strlen("Hello from UDP Server") + 1, 0,
           (struct sockaddr *)&client, len);

    close(sock);
    return 0;
}
