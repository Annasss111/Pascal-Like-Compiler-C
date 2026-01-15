/* main.c */ 
#include <stdio.h>
#include "lexical.c" // Inclut ts.c et tokens.h

const char* nom_token(int code) {
    switch(code) {
        case PROGRAM_TOKEN: return "PROGRAM";
        case VAR_TOKEN:     return "VAR";
        case BEGIN_TOKEN:   return "BEGIN";
        case END_TOKEN:     return "END";
        case IF_TOKEN:      return "IF";
        case THEN_TOKEN:    return "THEN";
        case ELSE_TOKEN:    return "ELSE";
        case WHILE_TOKEN:   return "WHILE";
        case DO_TOKEN:      return "DO";
        case READ_TOKEN:    return "READ";
        case READLN_TOKEN:  return "READLN";
        case WRITE_TOKEN:   return "WRITE";
        case WRITELN_TOKEN: return "WRITELN";
        case INTEGER_TOKEN: return "INTEGER";
        case CHAR_TOKEN:    return "CHAR";
        
        case PV_TOKEN:      return "PV (;)";
        case PT_TOKEN:      return "PT (.)";
        case DP_TOKEN:      return "DP (:)";
        case VIR_TOKEN:     return "VIR (,)";
        case PO_TOKEN:      return "PO ( ( )";
        case PF_TOKEN:      return "PF ( ) )";
        
        case AFF_TOKEN:     return "AFF (:=)";
        case EQ_TOKEN:      return "OPREL (=)";
        case NEQ_TOKEN:     return "OPREL (<>)";
        case LT_TOKEN:      return "OPREL (<)";
        case LE_TOKEN:      return "OPREL (<=)";
        case GT_TOKEN:      return "OPREL (>)";
        case GE_TOKEN:      return "OPREL (>=)";
        
        case PLUS_TOKEN:    return "OPER (+)";
        case MOINS_TOKEN:   return "OPER (-)";
        case MULT_TOKEN:    return "OPER (*)";
        case DIV_TOKEN:     return "OPER (/)";
        case MOD_TOKEN:     return "OPB (%)";
        case OR_TOKEN:      return "OPB (||)";
        case AND_TOKEN:     return "OPB (&&)";
        
        case ID_TOKEN:      return "ID";
        case NUM_TOKEN:     return "NUM";
        case EOF_TOKEN:     return "EOF";
        default:            return "INCONNU";
    }
}

int main() {
    fichier_source = fopen("test.p", "r");
    if (fichier_source == NULL) {
        printf("Erreur : Impossible d'ouvrir test.p\n");
        return 1;
    }

    lire_car(); 

    printf("\n");
    printf("############################################################\n");
    printf("#           TABLEAU 1 : FLUX DES SYMBOLES                  #\n");
    printf("############################################################\n");
    printf("| %-15s | %-15s | %-10s |\n", "LEXEME", "UNITE LEXICALE", "CODE");
    printf("|-----------------|-----------------|------------|\n");

    int ul;
    do {
        ul = AnalLex();
        if (ul != EOF_TOKEN && ul != 0) {
            printf("| %-15s | %-15s | %-10d |\n", chaine_lue, nom_token(ul), ul);
        }
    } while (ul != EOF_TOKEN);
    
    printf("------------------------------------------------------------\n\n");

    printf("############################################################\n");
    printf("#       TABLEAU 2 : TABLE DES IDENTIFICATEURS              #\n");
    printf("############################################################\n");
    printf("| %-10s | %-20s |\n", "INDEX", "NOM IDENTIFICATEUR");
    printf("|------------|----------------------|\n");

    for (int i = 0; i < NB_SYMBOLES; i++) {
        printf("| %-10d | %-20s |\n", i, TABLE_SYMBOLES[i].nom);
    }
    printf("-------------------------------------\n");

    fclose(fichier_source);
    return 0;
}