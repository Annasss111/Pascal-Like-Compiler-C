/* lexical.c */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "tokens.h" 
#include "ts.c"     

FILE *fichier_source;
char car_courant;       
char chaine_lue[50];    
char id_lex[20];         
int nb_val;              

void lire_car() {
    car_courant = fgetc(fichier_source);
}

int AnalLex() {
    while (car_courant == ' ' || car_courant == '\t' || car_courant == '\n' || car_courant == '\r') {
        lire_car();
    }

    if (car_courant == EOF) {
        strcpy(chaine_lue, "EOF");
        return EOF_TOKEN;
    }

    if (isalpha(car_courant)) {
        int i = 0;
        do {
            if (i < 19) id_lex[i++] = car_courant;
            lire_car();
        } while (isalnum(car_courant));
        
        id_lex[i] = '\0';
        strcpy(chaine_lue, id_lex); // Pour l'affichage

        if (strcasecmp(id_lex, "program") == 0) return PROGRAM_TOKEN;
        if (strcasecmp(id_lex, "var") == 0)     return VAR_TOKEN;
        if (strcasecmp(id_lex, "begin") == 0)   return BEGIN_TOKEN;
        if (strcasecmp(id_lex, "end") == 0)     return END_TOKEN;
        if (strcasecmp(id_lex, "if") == 0)      return IF_TOKEN;
        if (strcasecmp(id_lex, "then") == 0)    return THEN_TOKEN;
        if (strcasecmp(id_lex, "else") == 0)    return ELSE_TOKEN;
        if (strcasecmp(id_lex, "while") == 0)   return WHILE_TOKEN;
        if (strcasecmp(id_lex, "do") == 0)      return DO_TOKEN;
        if (strcasecmp(id_lex, "read") == 0)    return READ_TOKEN;
        if (strcasecmp(id_lex, "readln") == 0)  return READLN_TOKEN;
        if (strcasecmp(id_lex, "write") == 0)   return WRITE_TOKEN;
        if (strcasecmp(id_lex, "writeln") == 0) return WRITELN_TOKEN;
        if (strcasecmp(id_lex, "integer") == 0) return INTEGER_TOKEN;
        if (strcasecmp(id_lex, "char") == 0)    return CHAR_TOKEN;

        rangerId(id_lex);
        return ID_TOKEN;
    }

    if (isdigit(car_courant)) {
        int val = 0;
        do {
            val = val * 10 + (car_courant - '0');
            lire_car();
        } while (isdigit(car_courant));
        
        nb_val = val;
        sprintf(chaine_lue, "%d", nb_val); 
        return NUM_TOKEN;
    }

    switch (car_courant) {
        case ';': lire_car(); strcpy(chaine_lue, ";"); return PV_TOKEN;
        case '.': lire_car(); strcpy(chaine_lue, "."); return PT_TOKEN;
        case ',': lire_car(); strcpy(chaine_lue, ","); return VIR_TOKEN;
        case '(': 
            lire_car();
            if (car_courant == '*') {
                lire_car(); 
                char prec = ' ';
                while (car_courant != EOF) {
                    if (prec == '*' && car_courant == ')') {
                        lire_car(); 
                        return AnalLex(); 
                    }
                    prec = car_courant;
                    lire_car();
                }
            }

            strcpy(chaine_lue, "(");
            return PO_TOKEN;
            
        case ')': lire_car(); strcpy(chaine_lue, ")"); return PF_TOKEN;
        case '+': lire_car(); strcpy(chaine_lue, "+"); return PLUS_TOKEN;
        case '-': lire_car(); strcpy(chaine_lue, "-"); return MOINS_TOKEN;
        case '*': lire_car(); strcpy(chaine_lue, "*"); return MULT_TOKEN;
        case '/': lire_car(); strcpy(chaine_lue, "/"); return DIV_TOKEN;
        case '=': lire_car(); strcpy(chaine_lue, "="); return EQ_TOKEN;
        case ':':
            lire_car();
            if (car_courant == '=') {
                lire_car();
                strcpy(chaine_lue, ":=");
                return AFF_TOKEN;
            }
            strcpy(chaine_lue, ":");
            return DP_TOKEN;

        case '<':
            lire_car();
            if (car_courant == '=') {
                lire_car(); strcpy(chaine_lue, "<="); return LE_TOKEN;
            }
            if (car_courant == '>') {
                lire_car(); strcpy(chaine_lue, "<>"); return NEQ_TOKEN;
            }
            strcpy(chaine_lue, "<");
            return LT_TOKEN;

        case '>':
            lire_car();
            if (car_courant == '=') {
                lire_car(); strcpy(chaine_lue, ">="); return GE_TOKEN;
            }
            strcpy(chaine_lue, ">");
            return GT_TOKEN;

        default:
            printf("Erreur lexicale : caractere '%c' non reconnu\n", car_courant);
            lire_car();
            return 0; // Erreur
    }
}