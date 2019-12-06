#include <stdio.h>
#include "../lib/dotenv.c"

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

int main(void)
{
    env_load(".", false);
    //char *connection = getenv("SERVER_PORT");
    
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        return 0;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        char aux[MAXLINE];
        int len, n;
        n = recvfrom(sockfd, aux, MAXLINE,
                     MSG_WAITALL, (struct sockaddr *)&cliaddr,
                     &len);
        aux[n] = '\0';
        printf("%s\n",aux);
    }

    //printf("%d\n", read_next(&aux));
    //printf("%s\n", aux);

    return 0;
}

int read_next(char *result)
{

    return 1;
    // sendto(sockfd, (const char *)hello, strlen(hello),
    //     MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
    //         len);
    // printf("Hello message sent.\n");
}
