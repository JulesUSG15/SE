#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
int main() {
    pid_t pid;
    printf("Debut. \n");
    printf("P1 : mon pid est %d, mon ppid est %d. \n", (int) getpid(), (int)
    getppid());
    pid = fork();
    if (pid == 0) {
        printf("P2 : mon pid est %d, mon ppid est %d. \n", (int) getpid(),
        (int) getppid());
    }
    else {
        printf ("Je suis %d et mon fils est %d. \n", getpid(), pid);
        pid = fork();
        if (pid == 0) {
            printf("P3 : mon pid est %d, mon ppid est %d. \n", (int) getpid(),
            (int) getppid());
            pid = fork();
            if(pid == 0) {
                printf("P5 : mon pid est %d, mon ppid est %d. \n", (int)
                getpid(), (int) getppid());
            }
            else {
                printf ("Je suis %d et mon fils est %d. \n", getpid(), pid);
                pid = fork();
                if(pid == 0) {
                    printf("P6 : mon pid est %d, mon ppid est %d. \n", (int)
                    getpid(), (int) getppid());
                }
                else {
                    printf ("Je suis %d et mon fils est %d. \n", getpid(),
                    pid);
                }
            }
        }
        else {
            printf ("Je suis %d et mon fils est %d. \n", getpid(), pid);
            pid = fork();
            if (pid == 0) {
                printf("P4 : mon pid est %d, mon ppid est %d. \n", (int)
                getpid(), (int) getppid());
            }
            else {
                printf ("Je suis %d et mon fils est %d. \n", getpid(), pid);
            }
        }
    }
    return 0;
}