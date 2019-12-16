/* 
Código do programa cliente que obtém os dados da máquina e os envia para o servidor a fim de serem organizados e armazenados.

Baseado na fonte :
https://www.geeksforgeeks.org/udp-server-client-implementation-c/
Acesso em 05/12/2019

Autores:
Giovanni Oliveira
Henrique Rodrigues
*/

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
char cont[3*MAXLINE];
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
	fflush(stdin);
    fp = popen(command,"r");
	
	if(fp==NULL){
		puts("Erro. Comando não foi executado");
	}    
    content = read_buf(fp);
    pclose(fp);
    return content;
};

int main(void)
{	
	
         
	    
	    
		
	    char *id;
	    char *password;
	    char *keys;
	    char *p;
	    
	    

	    int sockfd;
	    struct sockaddr_in servaddr;
		int j;
	    
	
		j=0;
		env_load(".", false);
		id = getenv("ID");
	    password = getenv("PASSWORD");
	    keys = getenv("KEYS");


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

	    
	    for (p = strtok(keys, ","); p != NULL; p = strtok(NULL, ","))
	    {
		buffer[0] = '\0';
		strcat(buffer,id);
		strcat(buffer,",");
		strcat(buffer,password);
		strcat(buffer,",");
		strcat(buffer,p);
		strcat(buffer,",");
		aux=(char*)malloc(sizeof(buffer));
		conteudo=run_command(getenv(p));
		
		strcpy(aux,conteudo);
		strcat(buffer,aux);
		
		free(aux);
		
		int n, len;
		sendto(sockfd, (const char *)buffer, strlen(buffer),
		       MSG_CONFIRM, (const struct sockaddr *)&servaddr,
		       sizeof(servaddr));
	    }   
		close(sockfd);
		p=0;
		keys[0]='\0';
		
	    
    
    return 0;
}
