/* codegen.c */
#include <stdio.h>

int COMPTEUR_ETIQUETTE = 0;

int CreerEtiquette() {
    COMPTEUR_ETIQUETTE++;
    return COMPTEUR_ETIQUETTE;
}

void Emettre(char* op, int arg) {
    if (arg == -1) {
        printf("\t%s\n", op); 
        printf("\t%s\t%d\n", op, arg); 
    }
}