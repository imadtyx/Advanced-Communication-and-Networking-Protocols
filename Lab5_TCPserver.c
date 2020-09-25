#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int socket_fd)
{
    char buffer[MAX];
    int n;

    for (;;)
    {
        bzero(buffer, MAX);

        read(socket_fd, buffer, sizeof(buffer));
        printf("From client: %s\t To client : ", buffer);

        bzero(buffer, MAX);

        n = 0;
        while ((buffer[n++] = getchar()) != '\n');

        write(socket_fd, buffer, sizeof(buffer));

        if (strncmp("exit", buffer, 4) == 0)
        {
            printf("Server Exit...\n");
            break;
        }
    }
}

int main()
{
    int socket_fd, connection_fd, len;
    struct sockaddr_in server_address, cli;

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd == -1)
    {
        printf("Socket creation failed...\n");
        exit(0);
    }
    else printf("Socket successfully created..\n");

    bzero(&server_address, sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);

    if ((bind(socket_fd, (SA*)&server_address, sizeof(server_address))) != 0)
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    else printf("Socket bind successful..\n");

    if ((listen(socket_fd, 5)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else printf("Server listening..\n");

    len = sizeof(server_address);
    connection_fd = accept(socket_fd, (SA*)&cli, &len);

    if (connection_fd < 0)
    {
        printf("server accept failed...\n");
        exit(0);
    }
    else printf("server accept the client...\n");

    func(connection_fd);
    close(socket_fd);
}
