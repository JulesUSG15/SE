#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int N = 3; // Nombre de processus à créer en plus du processus initial.
    pid_t pid;
    int i;

    for (i = 0; i < N; i++) {
        pid = fork();
        if (pid == 0) {
            // Processus enfant
            printf("Processus %d créé par processus %d\n", getpid(), getppid());
        } else {
            // Processus parent attend la fin du processus enfant
            wait(NULL);
            break; // Le processus parent ne crée pas plus de processus
        }
    }
    return 0;
}