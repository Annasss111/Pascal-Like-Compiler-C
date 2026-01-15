/* ts.c */
#ifndef TS_C  
#define TS_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char nom[20];
    int type;     
    int adresse; 
} Symbole;


Symbole TABLE_SYMBOLES[100]; 
int NB_SYMBOLES = 0;         
int OFFSET_COURANT = 0;      



int rechercher(char* nom) {
    for (int i = 0; i < NB_SYMBOLES; i++) {
        if (strcmp(TABLE_SYMBOLES[i].nom, nom) == 0) {
            return i;
        }
    }
    return -1;
}

void rangerId(char* nom) {
    if (rechercher(nom) == -1) {
        if (NB_SYMBOLES < 100) {
            strcpy(TABLE_SYMBOLES[NB_SYMBOLES].nom, nom);
            TABLE_SYMBOLES[NB_SYMBOLES].type = -1;   
            TABLE_SYMBOLES[NB_SYMBOLES].adresse = -1; 
            NB_SYMBOLES++;
        } else {
            printf("Erreur : Table des symboles pleine !\n");
            exit(1);
        }
    }
}

void MettreAJourType(int type) {


    for (int i = 0; i < NB_SYMBOLES; i++) {
        if (TABLE_SYMBOLES[i].type == -1) {
            TABLE_SYMBOLES[i].type = type;
            TABLE_SYMBOLES[i].adresse = OFFSET_COURANT;
            OFFSET_COURANT++; 
        }
    }
}

int GetType(char* nom) {
    int idx = rechercher(nom);
    if (idx != -1) return TABLE_SYMBOLES[idx].type;
    return -1; // Erreur
}

int GetAdresse(char* nom) {
    int idx = rechercher(nom);
    if (idx != -1) return TABLE_SYMBOLES[idx].adresse;
    return -1; // Erreur
}

#endif 