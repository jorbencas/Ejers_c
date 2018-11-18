#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pidAB, pidBE, pidBG, pidBF, pidAC, pidAD;
    int status1, op1, op2;

    //int op1 = 4, op2 = 5;
    printf("Introdueix PRIMER operand: \n");
    fflush(stdin);
    scanf("%d", &op1);

    printf("Introdueix SEGON operand: \n");
    fflush(stdin);
    scanf("%d", &op2);

    /* A */
    pidAB = fork();
    if (pidAB == 0)
    { /* B*/

        if ((pidBE = fork()) == 0)
        { /* E */
            printf("Soc E (%d, fill de %d). Op matematica 1r operand al QUADRAT: %d\n", getpid(), getppid(), op1 * op1);
            sleep(3);
            exit(EXIT_SUCCESS);
        }
        /*B*/

        if ((pidBF = fork()) == 0)
        { /* F */
            waitpid(pidBE, &status1, 0);
            printf("Soc F (%d, fill de %d). Op matematica 2n operand al QUADRAT: %d\n", getpid(), getppid(), op2 * op2);
            sleep(3);
            exit(EXIT_SUCCESS);
        }
        /*B*/

        if ((pidBG = fork()) == 0)
        { /* G */
            waitpid(pidBF, &status1, 0);
            printf("Soc G (%d, fill de %d). Op matematica MITJANA 2 operands: %f\n", getpid(), getppid(), (double)(op1 + op2) / 2);
            sleep(3);
            exit(EXIT_SUCCESS);
        } //endif

        /* B */
        waitpid(pidBG, &status1, 0);
        printf("Soc B (%d, fill de %d). Op matematica SUMA dos operands: %d\n", getpid(), getppid(), op1 + op2);
        sleep(3);
        exit(EXIT_SUCCESS);
    } //endif B
    else
    {
        /* A */
        waitpid(pidAB, &status1, 0);
        if ((pidAC = fork()) == 0)
        { /* C */

            printf("Soc el C (%d, fill de %d). Op matematica RESTA dos operands: %d\n", getpid(), getppid(), op1 - op2);
            sleep(3);
            exit(EXIT_SUCCESS);
        }
        /* A */

        if ((pidAD = fork()) == 0)
        { /* D */

            printf("Soc el D (%d, fill de %d). Op matematica MULTIPLICACIO dos operands: %d\n", getpid(), getppid(), op1 * op2);
            sleep(3);
            exit(EXIT_SUCCESS);

        } //endif D

        /* A */

        //waitpid(pidAC, &status1, 0);
        waitpid(pidAD, &status1, 0);
        printf("Soc el A (%d, fill de %d). Valor dels DOS operands: %d, %d\n", getpid(), getppid(), op1, op2);
        sleep(3);
    } //endelse

    return 0;
}
