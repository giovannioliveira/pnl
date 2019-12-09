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

char buffer[2*MAXLINE];

int main(void)
{
    env_load(".", false);

    char *id = getenv("ID");
    char *password = getenv("PASSWORD");
    char *keys = getenv("KEYS");

    int sockfd;
    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    char *p;
    for (char *p = strtok(keys, ","); p != NULL; p = strtok(NULL, ","))
    {
        buffer[0] = '\0';
        strcat(buffer,id);
        strcat(buffer,",");
        strcat(buffer,password);
        strcat(buffer,",");
        strcat(buffer,"CALLING: ");
        strcat(buffer,p);

        
        int n, len;
        sendto(sockfd, (const char *)buffer, strlen(buffer),
               MSG_CONFIRM, (const struct sockaddr *)&servaddr,
               sizeof(servaddr));
    }
    close(sockfd);
    return 0;
}
