#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

    
    
     int main()
{
    int fd[2];
    pid_t pid;
    char saludopare[] = "Bon dia fill.\0";
    char buffer[80];
    pipe(fd);     //creem pipe
    pid = fork(); //creem procés
    switch (pid)
    {
    case -1: //ERROR
        printf("No s'ha pogut crear fill...");
        exit(-1);
    case 0:                                  //fill reb
        close(fd[1]);                        //tanca el descriptor d'entrada
        read(fd[0], buffer, sizeof(buffer)); //llig del pipe 80 bytes
        printf("\El fill reb algo del pipe: %s\n", buffer);
        break;
    default:          //pare envia
        close(fd[0]); //tanca el descriptor d'entradawrite(fd[1],saludopare, strlen(saludopare)); //escriu al pipe
        printf("\El pare envia missatge al fill\n", buffer);
        wait(NULL); //espera al procés fill
        break;
    }
    return 0;
}