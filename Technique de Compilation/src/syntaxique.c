#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"
#include "codegen.c"

// Variables externes
extern int AnalLex();
extern char id_lex[20]; 
extern int nb_val;
extern FILE *fichier_source;
int SYM_COUR;

extern void MettreAJourType(int type);
extern int GetType(char* nom);
extern int GetAdresse(char* nom);
extern void Emettre(char* op, int arg);
extern int CreerEtiquette();

void P();
void Dcl();
void Liste_id();
void Liste_id_prime(); 
void Type();
void Inst_composee();
void Inst();
void Liste_inst();
void Liste_inst_prime(); 
void I();
void Exp();
void Exp_prime();        
void Exp_simple();
void Exp_simple_prime(); 
void Terme();
void Terme_prime();      
void Facteur();

void Symbole_Suivant() {
    SYM_COUR = AnalLex();
}

void Erreur(char *message) {
    printf("ERREUR : %s\n", message);
    exit(1);
}

void Accepter(int t) {
    if (SYM_COUR == t) {
        Symbole_Suivant();
    } else {
        printf("Erreur fatale : Attendu code %d, recu %d\n", t, SYM_COUR);
        Erreur("Symbole inattendu");
    }
}


void P() {
    Accepter(PROGRAM_TOKEN);
    Accepter(ID_TOKEN);
    Accepter(PV_TOKEN);
    Dcl();
    
    printf("START\n"); 
    Inst_composee();
    printf("HLT\n");   
    
    Accepter(PT_TOKEN);
}

void Dcl() {
    if (SYM_COUR == VAR_TOKEN) {
        Accepter(VAR_TOKEN);
        Liste_id();
        Accepter(DP_TOKEN);
        Type(); 
        Accepter(PV_TOKEN);
        Dcl();
    }
}

void Liste_id() {
    Accepter(ID_TOKEN);

    Liste_id_prime();
}

void Liste_id_prime() {
    if (SYM_COUR == VIR_TOKEN) {
        Accepter(VIR_TOKEN);
        Accepter(ID_TOKEN);
        Liste_id_prime();
    }
}

void Type() {
    if (SYM_COUR == INTEGER_TOKEN) {
        MettreAJourType(T_ENTIER); 
        Accepter(INTEGER_TOKEN);
    } else if (SYM_COUR == CHAR_TOKEN) {
        MettreAJourType(T_CHAR);
        Accepter(CHAR_TOKEN);
    } else {
        Erreur("Type attendu");
    }
}

void Inst_composee() {
    Accepter(BEGIN_TOKEN);
    Inst();
    Accepter(END_TOKEN);
}

void Inst() {
    if (SYM_COUR == ID_TOKEN || SYM_COUR == IF_TOKEN || 
        SYM_COUR == WHILE_TOKEN || SYM_COUR == READ_TOKEN || 
        SYM_COUR == WRITE_TOKEN || SYM_COUR == BEGIN_TOKEN) {
        Liste_inst();
    }
}

void Liste_inst() {
    I();
    Liste_inst_prime();
}

void Liste_inst_prime() {
    if (SYM_COUR == PV_TOKEN) {
        Accepter(PV_TOKEN);
        if (SYM_COUR == END_TOKEN) return;
        I();
        Liste_inst_prime();
    }
}

void I() {
    char nomVar[20];
    int label1, label2;

    switch (SYM_COUR) {
        case ID_TOKEN:
            strcpy(nomVar, id_lex); 

            if (GetAdresse(nomVar) == -1) Erreur("Variable non declaree");
            
            Accepter(ID_TOKEN);
            Accepter(AFF_TOKEN);
            
            Exp(); 

            Emettre("STO", GetAdresse(nomVar)); 
            break;

        case IF_TOKEN:
            Accepter(IF_TOKEN);
            Exp(); 
            
            label1 = CreerEtiquette();
            Emettre("SIFAUX", label1);
            
            Accepter(THEN_TOKEN);
            I(); 
            
            label2 = CreerEtiquette();
            Emettre("SAUT", label2); 
            
            printf("L%d:\n", label1); 
            
            if (SYM_COUR == ELSE_TOKEN) {
                Accepter(ELSE_TOKEN);
                I(); 
            }
            
            printf("L%d:\n", label2); 
            break;

        case WHILE_TOKEN:
            Accepter(WHILE_TOKEN);
            
            label1 = CreerEtiquette(); 
            printf("L%d:\n", label1);
            
            Exp(); 
            
            label2 = CreerEtiquette(); 
            Emettre("SIFAUX", label2);
            
            Accepter(DO_TOKEN);
            I(); 
            
            Emettre("SAUT", label1); 
            printf("L%d:\n", label2); 
            break;

        case WRITE_TOKEN:
            Accepter(WRITE_TOKEN);
            Accepter(PO_TOKEN);
            
            if (GetAdresse(id_lex) == -1) Erreur("Variable non declaree (Write)");
            Emettre("LDV", GetAdresse(id_lex)); 
            Emettre("PRN", -1); 
            
            Accepter(ID_TOKEN);
            Accepter(PF_TOKEN);
            break;
            
        case BEGIN_TOKEN:
            Inst_composee();
            break;

        default: break; 
    }
}

void Exp() {
    Exp_simple();
    Exp_prime();
}

void Exp_prime() {
    if (SYM_COUR == GT_TOKEN) {
        Symbole_Suivant();
        Exp_simple();
        Emettre("GT", -1); 
    } 
    else if (SYM_COUR == LT_TOKEN) {
        Symbole_Suivant();
        Exp_simple();
        Emettre("LT", -1);
    }
    else if (SYM_COUR == EQ_TOKEN) {
        Symbole_Suivant();
        Exp_simple();
        Emettre("EQ", -1);
    }

}

void Exp_simple() {
    Terme();
    Exp_simple_prime();
}

void Exp_simple_prime() {
    if (SYM_COUR == PLUS_TOKEN) {
        Symbole_Suivant();
        Terme();
        Emettre("ADD", -1); 
        Exp_simple_prime();
    } else if (SYM_COUR == MOINS_TOKEN) {
        Symbole_Suivant();
        Terme();
        Emettre("SUB", -1);
        Exp_simple_prime();
    }
}

void Terme() {
    Facteur();
    Terme_prime();
}

void Terme_prime() {
    if (SYM_COUR == MULT_TOKEN) {
        Symbole_Suivant();
        Facteur();
        Emettre("MUL", -1);
        Terme_prime();
    } else if (SYM_COUR == DIV_TOKEN) {
        Symbole_Suivant();
        Facteur();
        Emettre("DIV", -1);
        Terme_prime();
    }
}

void Facteur() {
    if (SYM_COUR == ID_TOKEN) {
        if (GetAdresse(id_lex) == -1) {
            printf("Erreur sémantique: Variable '%s' non declaree\n", id_lex);
            exit(1);
        }

        Emettre("LDV", GetAdresse(id_lex));
        Accepter(ID_TOKEN);
    } else if (SYM_COUR == NUM_TOKEN) {

        Emettre("LDI", nb_val);
        Accepter(NUM_TOKEN);
    } else if (SYM_COUR == PO_TOKEN) {
        Accepter(PO_TOKEN);
        Exp();
        Accepter(PF_TOKEN);
    } else {
        Erreur("Facteur attendu");
    }
}
