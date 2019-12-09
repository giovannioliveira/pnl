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
#define DAY 86400

char buffer[3*MAXLINE];

char *conteudo;
char cont[2*MAXLINE];
char lin[2*MAXLINE];

char* aux;



int clean_buf(char *buf){
    buf[0]='\0';
    return 0;
};



char* read_buf(FILE *input){
    
    clean_buf(cont);
    while(fgets(lin,sizeof(input),input)){
        strcat(cont,lin);
    }
    return cont;
};

char* run_command(char *command){
    FILE *fp;
    char *content;
    fp= popen(command,"r");    
    content = read_buf(fp);
    pclose(fp);
    return content;
};

int main(void)
{	
    //while(1){
          
	    //sleep(5);
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
		strcat(buffer,p);
		strcat(buffer,",");
		strcat(buffer,"\n");
		run_command(getenv(p));
		aux=(char*)malloc(sizeof(buffer));
		conteudo=run_command(getenv(p));
		strcpy(aux,conteudo);
		strcat(buffer,aux);
		
		
		
		int n, len;
		sendto(sockfd, (const char *)buffer, strlen(buffer),
		       MSG_CONFIRM, (const struct sockaddr *)&servaddr,
		       sizeof(servaddr));
	    }   
	    close(sockfd);
            
    //}
    return 0;
}
