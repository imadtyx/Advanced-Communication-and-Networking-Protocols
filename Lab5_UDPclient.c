#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>
  
#define PORT    8080 
#define MAXLINE 1024 

// Driver code
int main() {
    int sockfd;
    char buffer[MAXLINE];
    char hello[100];
    struct sockaddr_in servaddr;
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
    while(1){
        int n, len;
        fgets(hello, 100, stdin);
        sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
        printf("Client Waiting\n\n");
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
        buffer[n] = '\0';
        time_t curtime = time (NULL);
        struct tm *loc_time = localtime(&curtime);
        printf("\n%sFrom Server : %s\tTo Server: ", asctime(loc_time), buffer);
    }
    close(sockfd);
    return 0;
}
