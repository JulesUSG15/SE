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

#### Programme `terminaison.c`

- **Questions à répondre**:
    1. Nombre de processus créés, affichages effectués, et justification.
    2. Effet de la suppression de `exit(2)`.
    3. Création d'un processus zombie pendant 30 secondes et vérification.
    4. Effet de l'ajout de `sleep(30)` avant `exit(1)`.

### 3. La Primitive exec

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