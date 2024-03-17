# TP 2

## 1. Création de Processus: Utilisation de fork

### Programme `fork1.c`

- **Question Prévoyez le résultat**: Le programme affiche d'abord "debut", puis crée un processus fils. Le processus fils incrémentera `x` et affichera son PID, celui de son parent, et la valeur de `x`. Le processus parent décrémentera `x` et affichera son PID, le PID de son fils, et la valeur de `x`. Finalement, "Fin" sera affiché deux fois: une fois par le processus parent et une fois par le fils.

- **Arbre des processus**: Le processus parent (P) crée un processus fils (F).

- **Compilation et test**: 
```
┌──(jules@jules-MacBookPro)-[~/Documents/Polytech/SE/output]  
└─$ ./"fork1"  
debut  
parent: je suis 12410, parent de 12411 et fils de 9558. x=0  
Fin  
child : je suis 12411, fils de 12410. x=2  
Fin  
```

## 1.1 Fork Imbriqué

- **Programme à écrire**: 
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    printf("Debut. \n");
    printf("P1 : mon pid est %d, mon ppid est %d. \n", (int) getpid(), (int) getppid());
    pid = fork();
    if (pid == 0) {
        printf("P2 : mon pid est %d, mon ppid est %d. \n", (int) getpid(), (int) getppid());
    }
    else {
        printf ("Je suis %d et mon fils est %d. \n", getpid(), pid);
        pid = fork();
        if (pid == 0) {
            printf("P3 : mon pid est %d, mon ppid est %d. \n", (int) getpid(), (int) getppid());
            pid = fork();
            if(pid == 0) {
                printf("P5 : mon pid est %d, mon ppid est %d. \n", (int) getpid(), (int) getppid());
            }
            else {
                printf ("Je suis %d et mon fils est %d. \n", getpid(), pid);
                pid = fork();
                if(pid == 0) {
                    printf("P6 : mon pid est %d, mon ppid est %d. \n", (int) getpid(), (int) getppid());
                }
                else {
                    printf ("Je suis %d et mon fils est %d. \n", getpid(), pid);
                }
            }
        }
        else {
            printf ("Je suis %d et mon fils est %d. \n", getpid(), pid);
            pid = fork();
            if (pid == 0) {
                printf("P4 : mon pid est %d, mon ppid est %d. \n", (int) getpid(), (int) getppid());
            }
            else {
                printf ("Je suis %d et mon fils est %d. \n", getpid(), pid);
            }
        }
    }
    return 0;
}
```

- **Résultat obtenue**:
```
┌──(jules@jules-MacBookPro)-[~/Documents/Polytech/SE/output]  
└─$ ./"1.1"  
Debut.  
P1 : mon pid est 15800, mon ppid est 9558.  
Je suis 15800 et mon fils est 15801.  
P2 : mon pid est 15801, mon ppid est 15800.  
Je suis 15800 et mon fils est 15802.  
P3 : mon pid est 15802, mon ppid est 15800.  
Je suis 15800 et mon fils est 15803.  
P4 : mon pid est 15803, mon ppid est 15800.  
Je suis 15802 et mon fils est 15804.  
P5 : mon pid est 15804, mon ppid est 15802.  
Je suis 15802 et mon fils est 15805.  
P6 : mon pid est 15805, mon ppid est 15802.   
```

- **Observation et commentaire sur l'ordre d'apparition des messages**: Je vois que l’ordre

 d’apparition des messages n’est pas l’ordre du code. Si je relance plusieurs fois le programme, j'observe que les PID et l’ordre d’apparition des messages changent. Je peux donc en déduire que les PID sont incrémentés et que l’ordre d’exécution des fils est aléatoire.

## 2. Terminaison de Processus

### Programme `terminaison.c`

### Question 1 : Donnez le nombre de processus créés, ainsi que les affichages effectués par chaque processus en justifiant.Vérifiez votre réponse en ajoutant des affichages dans le programme.

- **Nombre de processus créés**: 3 (le processus original `P1`, et deux processus fils `P2` et `P3`).
- **Affichages effectués**:
    - `P2` affichera `a : 20 \n` juste avant de terminer.
    - `P1` attend que `P2` termine et affichera `a : 10 ; e : 1 \n`, où `e` est le code de sortie de `P2` (1 dans ce cas).

`P3` ne fait pas d'affichage directement mais influence le code de sortie que `P2` peut récupérer si `P2` utilisait `wait()`. Cependant, dans ce code, `P2` termine sans attendre `P3`, donc le code de sortie de `P3` n'est pas récupéré ni affiché par `P2`.

- **Vérification par Affichage Supplémentaire**

Voici le nouveau code avec des affichages supplémentaires :
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int a, e;
    a = 10;
    printf("Start: PID=%d, PPID=%d\n", getpid(), getppid()); // Affiche le PID au début
    if (fork() == 0) {
        a = a *2;
        printf("P2: PID=%d, PPID=%d, a=%d\n", getpid(), getppid(), a); // P2 affiche son PID, PPID, et a
        if (fork() == 0) {
            a = a +1;
            printf("P3: PID=%d, PPID=%d, a=%d\n", getpid(), getppid(), a); // P3 affiche son PID, PPID, et a
            exit(2);
        }
        wait(NULL); // P2 attends P3 pour synchroniser l'affichage
        exit(1);
    }
    wait(&e);
    printf("P1: PID=%d, a=%d ; e=%d \n", getpid(), a, WEXITSTATUS(e)); // P1 affiche son PID, a, et le code de sortie de P2
    return(0);
}
```
Voici le résultat que j'obtiens :
```
┌──(jules@jules-MacBookPro)-[~/Documents/Polytech/SE/output]
└─$ ./"terminaison"
Start: PID=23654, PPID=9558
P2: PID=23655, PPID=23654, a=20
P3: PID=23656, PPID=23655, a=21
P1: PID=23654, a=10 ; e=1 
```

### Question 2 : On supprime l’instruction exit(2), reprenez la question précédente en conséquence.

1. **Premier processus fils** (`P2`):
    - Multiplie `a` par 2, donc `a = 20`.
    - Crée un processus fils (`P3`).
    - **Puisque `P3` n'effectue plus `exit(2)`, il continue l'exécution du reste du code dans `P2`.**
    - Affiche `a : 20 \n`.
    - Termine avec `exit(1)`.

2. **Second processus fils** (`P3`):
    - Incrémente `a` de 1, donc `a = 21`.
    - Poursuit l'exécution et effectue la même instruction d'affichage que `P2` (car il continue à exécuter le code après la condition `if (fork() == 0)` sans rencontrer un `exit()` précoce).
    - Affiche `a : 21 \n`.
    - Termine implicitement à la fin de `main()`, retournant 0 comme code de sortie par défaut (ceci n'est pas visible car `wait(&e)` dans le processus parent (`P1`) attend seulement le premier processus fils (`P2`)).

3. **Processus principal** (`P1`):
    - Ne modifie pas `a` après la création de `P2`, donc `a = 10`.
    - Attend que `P2` se termine et récupère son code de sortie via `e`.
    - Affiche `a : 10 ; e : 1 \n`.

Voici le résultat que j'obtiens :
```
┌──(jules@jules-MacBookPro)-[~/Documents/Polytech/SE/output]
└─$ ./"terminaison"
a : 20 
a : 21 
a : 10 ; e : 1 
```

### Question 3 : Modifiez le programme initial pour créer un processus zombie pendant 30 secondes.

```c
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
```

Dans ce programme, le "petit-enfant" s'endort pendant 30 secondes avant de se terminer. Cependant, son parent (l'enfant du processus initial) se termine presque immédiatement après sa création, sans attendre que le "petit-enfant" se termine. Cela crée une condition où le "petit-enfant" devient un processus zombie après sa terminaison, jusqu'à ce que le grand-parent (le processus initial) termine l'attente et nettoie le statut du zombie.

- **Vérification avec `ps -al`**
```
┌──(jules@jules-MacBookPro)-[~/Documents/Polytech/SE]
└─$ ps -al
F S   UID     PID    PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
0 S  1000    1781    1778  0  80   0 - 56593 do_sys tty2     00:00:00 gnome-session-b
0 S  1000   27958    9558  0  80   0 -   655 hrtime pts/0    00:00:00 terminaison
1 S  1000   27960    1729  0  80   0 -   655 hrtime pts/0    00:00:00 terminaison
4 R  1000   28028   28002  0  80   0 -  3858 -      pts/1    00:00:00 ps
```
### Question 4 : Ajoutez à votre programme précédent l’instruction sleep(30) à la ligne 11 (avant exit(1)). Que se passe-t-il ? Expliquez.

Si nous ajoutons `sleep(30);` juste avant `exit(1);` dans le processus enfant, le comportement du programme change de manière significative. Cette modification introduit une pause dans le processus enfant avant qu'il ne termine, permettant potentiellement au "petit-enfant" de terminer et d'éviter de devenir un zombie pendant que l'enfant dort. Voyons cela plus en détail.

### Programme Modifié avec `sleep(30)` Avant `exit(1)`

```c
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
            sleep(30); // Pause pour permettre au parent de devenir temporairement un zombie
            exit(2); // Le petit-enfant termine
        }
        sleep(30); // Ajout du sleep ici
        printf("Enfant se termine, PID = %d\n", getpid());
        exit(1);
    }
    else {
        // Le processus parent attend l'enfant
        wait(&e);
        printf("a : %d ; e : %d\n", a, WEXITSTATUS(e));
        sleep(35); // Assurez-vous que le parent attend assez longtemps pour observer le processus zombie
    }
    return 0;
}
```
1. **Processus parent (`P1`)**: Crée un processus enfant (`P2`) et attend sa terminaison avec `wait(&e)` avant d'entrer dans son propre `sleep(35)` pour assurer qu'il reste actif pour nettoyer tout processus zombie potentiel après le réveil.

2. **Processus enfant (`P2`)**: Multiplie `a` par 2 et crée un "petit-enfant" (`P3`). Au lieu de se terminer immédiatement, il entre maintenant en pause pour 30 secondes grâce au `sleep(30)` ajouté. Après cette pause, il imprime un message indiquant sa propre terminaison et se termine avec `exit(1)`.

3. **"Petit-enfant" (`P3`)**: Incrémente `a` de 1, dort également pour 30 secondes (comme avant), puis se termine avec `exit(2)`.

#### Effets de l'Ajout de `sleep(30)` Avant `exit(1)`

- **Synchronisation des Terminaisons**: L'ajout de `sleep(30)` avant `exit(1)` dans `P2` synchronise presque les terminaisons de `P2` et `P3`. Cela signifie que `P3` pourrait se terminer juste avant ou autour du même moment que `P2`. Si `P2` attend `P3` pour terminer grâce au `sleep()`, il y a moins de chances que `P3` devienne un zombie, car `P2` peut encore être en vie lorsque `P3` se termine. Néanmoins, si `P3` se termine avant que `P2` n'appelle `wait()`, il deviendra un zombie jusqu'à ce que `P2` se réveille et termine, permettant au processus parent de nettoyer.
- **Pas de Processus Zombie**: Avec les deux `sleep(30)` en place, il est très probable que le "petit-enfant" (`P3`) ne devienne pas un zombie du tout, car son processus parent (`P2`) ne se termine pas avant lui.

## 3. La Primitive exec

#### Programme `exec1.c`

- **Question**: Résultat de l'exécution et explication de qui affiche quoi et pourquoi.

#### Programme `exec2.c`

- **Représentation des processus et ordre de terminaison**: Je vais dessiner l'arbre de processus et discuter des ordres possibles de terminaison.

### 4. Création de Processus en Chaîne

- **Écriture du programme**: Pour N=3, rédiger le programme demandé, le représenter, et discuter des modifications pour que le processus initial attende soit uniquement la fin de son fils soit la fin de tous les processus créés.

Pour commencer, je vais compiler et tester le programme `fork1.c` pour répondre à la première série de questions. Ensuite, je procéderai étape par étape pour chaque exercice. Examinons d'abord `fork1.c`.

J'ai préparé le fichier `fork1.c` pour la compilation. Cependant, je ne peux pas compiler ou exécuter directement des programmes C dans cet environnement. Vous pouvez compiler et exécuter ce programme sur votre système en utilisant la commande suivante dans un terminal :

```
gcc -o fork1 /mnt/data/fork1_compiled.c && ./fork1
```

Après avoir exécuté le programme, veuillez observer les résultats, en particulier les valeurs de `x` affichées par le processus parent et le processus fils, ainsi que les PIDs et PPIDs. Cela vous aidera à répondre à la question sur le comportement de la variable `x` après l'appel à `fork()`.

En attendant, je vais continuer avec la description des autres parties du TP. Pour les exercices suivants, je vais fournir des explications théoriques et des directives pour vous aider à comprendre et à résoudre les exercices par vous-même.

### 1.1 Fork Imbriqué

Pour cet exercice, vous devez écrire un programme qui crée un arbre de processus selon le schéma donné dans l'énoncé du TP. Chaque processus doit afficher son PID et PPID, ainsi que les PIDs des fils qu'il engendre, s'il y en a. Pour observer l'ordre d'apparition des messages, exécutez plusieurs fois le programme et notez les variations.

### 2. Terminaison de Processus

Pour `terminaison.c`, vous devez comprendre comment `exit()` et `wait()` fonctionnent ensemble pour gérer la terminaison des processus. En particulier, observez comment la valeur de retour d'un processus fils est récupérée par le processus parent et comment un processus zombie est créé et géré.

### 3. La Primitive exec

Le fichier `exec1.c` montre comment un processus peut être remplacé par un autre programme en utilisant `execl()`. Après l'exécution de `exec1.c`, notez quel processus affiche quel message et pourquoi. Pour `exec2.c`, analysez comment les appels à `fork()` et `execl()` interagissent pour créer une structure de processus complexe.

### 4. Création de Processus en Chaîne

Enfin, pour l'exercice sur la création de processus en chaîne, vous devez écrire un programme où chaque processus crée un autre processus dans une séquence jusqu'à ce que N processus soient créés. Modifiez ensuite le programme pour contrôler comment le processus initial attend la fin des processus qu'il a créés.

Chaque exercice requiert que vous compreniez les interactions entre les processus parent et fils, ainsi que l'utilisation des appels système pour la gestion des processus. N'hésitez pas à compiler et exécuter les exemples sur votre machine pour observer leur comportement.