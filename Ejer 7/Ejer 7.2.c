#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int fp;
    char saludo[] = "Salutacions!!! \0";
    fp = open("FIFO1", 1);
    if (fp == -1)
    {
        printf("ERROR AL ABRIR fitxer\n");
        exit(1);
    }
    printf("enviant informació al fifo...\n");
    write(fp, saludo, strlen(saludo));
    close(fp);
    return 0;
}