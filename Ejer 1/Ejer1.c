#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main(int argc, char *argv[]){
pid_t pid, pid2;
int status1, status2;

if ( (pid=fork()) == 0 ){
   
    if ( (pid2=fork()) == 0 ){
        /* Net */
        printf("Soc el Net (%d) de (%d)\n", getpid(),getppid());
    }else{
         /* Pare */
        waitpid(pid2, &status2, 0);
        printf("Soc el Pare (%d) de (%d)\n", getpid(),getppid());
    }
}else{
    /* Avi */
    waitpid(pid, &status1, 0);
    printf("Soc el Avi (%d) de (%d)\n", getpid(), getppid());
}
return 0;
}