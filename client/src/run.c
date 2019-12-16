/* 
Código do executador que, em loop, chama o cliente de acordocom o tempo definido de intervalo.

Autores:
Giovanni Oliveira
Henrique Rodrigues
*/


#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "../lib/dotenv.c"
#include <stdlib.h>
#include <string.h>

char * const args[0];
char opt[2];
char pass[21];
char *keys;
char *p;

int main(){
    int pid;
    int c;
    puts("Bem vindo ao executador do cliente de monitoramento pnl.");
    

    puts("Para mudar alguma configuração basta alterar o arquivo .env\n");

    while(1){
        sleep(2);
        pid=fork();
        if(pid==0){
            execv("./client",args);
        }
        wait(&pid);
        
    }

    return 0;
}
