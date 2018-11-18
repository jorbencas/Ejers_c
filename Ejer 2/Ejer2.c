#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    pid_t pid1, pid2, pid3, pid4, pid5, pid6;
    int status1, status2, status3, status4, status5, status6;
    int operando1 = 3, operando2 = 4, resultado;
    pid1 = fork();
    if (pid1 == 0)
    {

        if ((pid4 = fork()) == 0)
        { /* segon fill */
            printf("Soc el Primer E fill (%d) fill de (%d)\n", getpid(), getppid());
        }
        else
        {
            if ((pid5 = fork()) == 0)
            { /* segon fill */
                waitpid(pid4, &status4, 0);
                printf("Soc el Segon F fill (%d) fill de (%d)\n", getpid(), getppid());
            }
            else
            {
                if ((pid6 = fork()) == 0)
                { /* segon fill */
                    waitpid(pid5, &status5, 0);
                    printf("Soc el Tercer G fill (%d) fill de (%d)\n", getpid(), getppid());
                }
                else
                {
                    waitpid(pid4, &status4, 0);

                    resultado = (operando1 + operando2);
                    /* fill */
                    printf("Soc el primer B fill (%d) fill de (%d) (%d) + (%d) = (%d)\n", getpid(), getppid(), operando2, operando1, resultado);
                }
            }
        }
    }
    else
    { /* pare */
        if ((pid2 = fork()) == 0)
        { /* segon fill */
            printf("Soc el segon C fill (%d) fill de (%d)\n", getpid(), getppid());
        }
        else
        {
            if ((pid3 = fork()) == 0)
            { /* segon fill */
                waitpid(pid1, &status1, 0);
                resultado = (operando2 - operando1);
                printf("Soc el tercer D fill (%d) fill de (%d) (%d) - (%d) = (%d)\n", getpid(), getppid(), operando2, operando1, resultado);
            }
            else
            {
                /* pare */
                /* Esperem que el primer fill acabe, status 0 */
                waitpid(pid1, &status1, 0);

                printf("Soc el pare A (%d) fill de (%d) Operandos (%d),(%d)\n", getpid(), getppid(), operando1, operando2);
            }
        }
    }
    return 0;
}
