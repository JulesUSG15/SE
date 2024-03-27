#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

void printInFile (FILE* fichier, int processNumber)
{
fprintf(fichier, "Execution du processus %d !\n", processNumber);
}
int main(void){

    FILE* fichier = NULL;//C'est un pointeur sur une structure de type FILE qui va permettre d'écrire dans le fichier.

    fichier = fopen("tpse/tests/t2/pingouin.txt", "w"); // ouvre le fichier, "w" est un mode d'ouverture en écriture seule.

    if (fichier == NULL){
	printf("fichier non trouvé");
	exit(EXIT_FAILURE); // oups !
    }

    //ajoutez votre code ici...
    //printInFile(fichier,1);
    



    fclose(fichier); // /!\ Ne pas oublier de fermer …
    exit(EXIT_SUCCESS);
}
