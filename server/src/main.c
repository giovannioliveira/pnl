#include <stdio.h>
#include "../lib/dotenv.c"

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>

#define PORT 8080
#define MAXLINE 1024

char *content;
char *token;
char msg[2*MAXLINE];
char dat[20];
char tim[20];
char tmp[5];
char fname[40];
char *mname;
int cont;
FILE *arq;
time_t temp;
struct tm *local;


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
    msg[0]='\0';
    while (1)
    {
        tim[0]='\0';
        time(&temp);
        local=localtime(&temp);
        dat[0]='\0';
	//montando a data
        sprintf(tmp,"%d",local->tm_mday);
        strcat(dat,tmp);
        strcat(dat,"_");
        sprintf(tmp,"%d",local->tm_mon+1);
        strcat(dat,tmp);
        strcat(dat,"_");
        sprintf(tmp,"%d",local->tm_year+1900);
        strcat(dat,tmp);
        puts(dat);
	//montando o horário
        sprintf(tmp,"%d",local->tm_hour);
        strcat(tim,tmp);
        strcat(tim,":");
        sprintf(tmp,"%d",local->tm_min);
        strcat(tim,tmp);
        strcat(tim,":");
        sprintf(tmp,"%d",local->tm_sec);
        strcat(tim,tmp);
        
	char aux[2*MAXLINE];
        int len, n;
        n = recvfrom(sockfd, aux, MAXLINE,
                     MSG_WAITALL, (struct sockaddr *)&cliaddr,
                     &len);
        aux[n] = '\0';
        cont=0;
        for (char *p = strtok(aux, ","); p != NULL; p = strtok(NULL, ",")){
            fname[0]='\0';
            if(cont==0){
		//obtém o nome da máquina
                mname=p;
            }
            if(cont==2){
		//obtém o token de função sendo processado: disk, memory, users
                token=p;
            }
            
            if(cont==3){//3 corresponde ao conteúdo resultado
		//verifica a que dado se refere e grava no arquivo correspondente
                if(!strcmp(token,"DISK")){
		    //montagem do nome do arquivo:nome_máquina+id_dado+data
                    strcat(fname,"./");
                    strcat(fname,mname);
                    strcat(fname,"disk");
                    strcat(fname,dat);
                    strcat(fname,".txt");
                    arq=fopen(fname,"a+");
                    if(arq==NULL){
                        printf("ERROR FILE");
                    }
		    //identifica cada volume de dados com o horário
                    fputs("Horário: ",arq);
                    fputs(tim,arq);
                    fputs(p,arq);
                    fflush(arq);
                }
                else{
                    if(!strcmp(token,"MEMORY")){
			//puts(getenv("LOG_PATH"));
                        //strcat(fname,"./");
			strcat(fname,getenv("LOG_PATH"));
                        strcat(fname,mname);
                        strcat(fname,"memory");
                        strcat(fname,dat);
                        strcat(fname,".txt");
                        arq=fopen(fname,"a+");
                        if(arq==NULL){
                            printf("ERROR FILE");
                        }
                        fputs("Horário: ",arq);
                        fputs(tim,arq);
                        fputs(p,arq);
                        fflush(arq);
                    }
                    else{
                        if(!strcmp(token,"USERS")){
                            strcat(fname,"./");
                            strcat(fname,mname);
                            strcat(fname,"users");
                            strcat(fname,dat);
                            strcat(fname,".txt");
                            arq=fopen(fname,"a+");
                            if(arq==NULL){
                                printf("ERROR FILE");
                            }
                            fputs("Horário: ",arq);
                            fputs(tim,arq);
                            fputs(p,arq);
                            fflush(arq);
                        }
                    }
                }
            }
            cont++;
        }
    }
    

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
