/* main2.c */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "tokens.h"


#include "lexical.c"
#include "syntaxique.c"

int main() {

    fichier_source = fopen("test.p", "r");
    if (fichier_source == NULL) {
        printf("ERREUR CRITIQUE : Impossible d'ouvrir le fichier test.p\n");
        return 1;
    }

    lire_car(); 

    Symbole_Suivant();

    printf("debut de l'analyse syntaxique...\n");
    printf("--------------------------------\n");

    P();

    if (SYM_COUR == EOF_TOKEN) {
        printf("\n--------------------------------\n");
        printf(">> SUCCES : Le programme est syntaxiquement CORRECT !\n");
        printf("--------------------------------\n");
    } else {
        printf("\n--------------------------------\n");
        printf(">> ECHEC : Fin de fichier inattendue.\n");
        printf("   L'analyse s'est arretee, mais il reste du code non lu.\n");
        printf("--------------------------------\n");
    }

    // Fermeture du fichier
    fclose(fichier_source);
    return 0;
}