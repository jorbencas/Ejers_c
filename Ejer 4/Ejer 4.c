#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
    int pid_t pid, pid2;
    char saludo[] = "Un saludo....";
    char buffer[10];
    int fd, bytesllegits;
    int status1, status2;

    if ((pid = fork()) == 0)
    {
        fd=open("text.txt",O_RDWR|O_CREAT,0644)); //fitxer obert per a escriptura
        //control de l'error en apertura fitxer
        if (fd == -1)
        {
            printf("ERROR al obrir fitxer");
            exit(-1);
        }
        // escriu saludo a fitxer i tanca
        printf("escric la salutació..");
        write(fd, saludo, strlen(saludo));
        close(fd);
       
    }
    else
    {
        waitpid(pid, &status1, 0);
        fd = open("text.txt", O_RDONLY); // fitxer obert per a lectura
        printf("contenido del fitxer \n");
        //llig bytes d'un en un i ho desa al buffer
        bytesllegits = read(fd, buffer, 1);
        while (bytesllegits != 0)
        {
            buffer[bytesllegits] = 0;           //especifiquem la finalitzacio de cadena
            printf("%s", buffer);               //escriu byte llegit
            bytesllegits = read(fd, buffer, 1); //llig altre byte
        }
        close(fd);
    }
    return 0;
}