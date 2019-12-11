#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char * const args[0];

int main(){
    int pid;
    while(1){
        sleep(2);
        pid=fork();
        if(pid==0){
            puts("PASSOU");
            execv("./client",args);
        }
        wait(&pid);
        
    }

    return 0;
}
