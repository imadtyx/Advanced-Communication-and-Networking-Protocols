#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int socket_fd)
{
    char buffer[MAX];
    int n;

    for (;;)
    {
        bzero(buffer, sizeof(buffer));

        printf("Enter the string : ");

        n = 0;
        while ((buffer[n++] = getchar()) != '\n');

        write(socket_fd, buffer, sizeof(buffer));

//        bzero(buffer, sizeof(buffer));
        memset(buffer, 0, sizeof(buffer));

        read(socket_fd, buffer, sizeof(buffer));

        printf("From Server : %s", buffer);

        if ((strncmp(buffer, "exit", 4)) == 0)
        {
            printf("Client Exit...\n");
            break;
        }
    }
}

int main()
{
    int socket_fd;
    struct sockaddr_in server_addr;

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else printf("Socket successfully created..\n");

    bzero(&server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    if (connect(socket_fd, (SA*)&server_addr, sizeof(server_addr)) != 0)
    {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else printf("connected to the server..\n");

    func(socket_fd);
    close(socket_fd);
}
