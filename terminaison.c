#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    int a, e;
    a = 10;
    if (fork() == 0) {
        a = a *2;
        if (fork() == 0) {
            a = a +1;
            exit(2);
        }
        printf("a : %d \n", a);
        exit(1);
    }
    wait(&e);
    printf("a : %d ; e : %d \n", a, WEXITSTATUS(e));
    return(0);
}
