/* main.c */
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
        printf("ERREUR : Impossible d'ouvrir test.p\n");
        return 1;
    }

    lire_car(); 
    Symbole_Suivant();

    printf("### COMPILATION DEBUT ###\n\n");
    printf("--- CODE GENERE (MACHINE A PILE) ---\n");

    P();

    if (SYM_COUR == EOF_TOKEN) {
        printf("\n--- COMPILATION REUSSIE ! ---\n");
        
        printf("\n[DEBUG] ETAT DE LA TABLE DES SYMBOLES :\n");
        for(int i=0; i<NB_SYMBOLES; i++) {
            printf("Var: %-10s | Type: %d | Adresse: %d\n", 
                   TABLE_SYMBOLES[i].nom, TABLE_SYMBOLES[i].type, TABLE_SYMBOLES[i].adresse);
        }
    } else {
        printf("\n--- ERREUR : Fin de fichier inattendue ---\n");
    }

    fclose(fichier_source);
    return 0;
}