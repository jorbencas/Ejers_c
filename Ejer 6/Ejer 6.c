#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int fd1[2],fd2[2];
    char buffer[30];
    pid_t pid, pid2;
    int status;

    pipe(fd1);
    pipe(fd2);
    pid=fork();

    if(pid == 0){
        if((pid2=fork()) == 0){ //Si estas en el Nieto == 0
            //waitpid(pid, &status, 0);
            printf("Soy el nieto: (%d), hijo de: (%d)\n", getpid(), getppid());
            read(fd2[0], buffer, 20);
            printf("Mensaje del Avi que rep el Net: %s \n", buffer);
            write(fd1[1], "Hola Abuelo", 15);
        }else{

            //Parte 1
            printf("Soy el padre: (%d), hijo de: (%d)\n", getpid(), getppid());
            read(fd1[0], buffer, 20);
            write(fd2[1], buffer, 20);

            // Parte 2
            waitpid(pid2, &status, 0);
            read(fd1[0], buffer, 20);
            write(fd2[1], buffer, 20);
        }
    }else{
        close(fd1[0]);
        write(fd1[1], "Hola Nieto", 15);
        printf("Soy el abuelo: (%d), hijo de: (%d)\n", getpid(), getppid());

        // Parte 2
        waitpid(pid, &status, 0);
        read(fd2[0], buffer, 20);
        printf("Mensaje del Net que rep el Avi: %s \n", buffer);
    }
    return 0;
}