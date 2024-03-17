#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int a, e;
    a = 10;
    pid_t pid = fork();
    
    if (pid == 0) { // Processus enfant
        a = a * 2;
        pid_t pid_child = fork();
        if (pid_child == 0) { // Enfant de l'enfant (petit-enfant)
            a = a + 1;
            printf("Petit-enfant en pause, PID = %d\n", getpid());
            sleep(30); // Pause pour créer un processus zombie
            exit(2); // Le petit-enfant termine
        }
        // Le processus enfant se termine immédiatement
        // Ne pas attendre le petit-enfant exprès pour créer un zombie
        exit(1);
    }
    else {
        // Le processus parent attend immédiatement l'enfant pour éviter un zombie ici
        wait(&e);
        printf("a : %d ; e : %d\n", a, WEXITSTATUS(e));
        // Le parent se termine rapidement, laissant le petit-enfant devenir un zombie temporairement
        sleep(35); // Attendre un peu plus longtemps que le petit-enfant pour observer le zombie
    }
    return 0;
}