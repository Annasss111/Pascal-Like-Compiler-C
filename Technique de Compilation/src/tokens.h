/* tokens.h */
#ifndef TOKENS_H
#define TOKENS_H

#define PROGRAM_TOKEN 1
#define VAR_TOKEN     2
#define BEGIN_TOKEN   3
#define END_TOKEN     4
#define IF_TOKEN      5
#define THEN_TOKEN    6
#define ELSE_TOKEN    7
#define WHILE_TOKEN   8
#define DO_TOKEN      9
#define READ_TOKEN    10
#define READLN_TOKEN  11
#define WRITE_TOKEN   12
#define WRITELN_TOKEN 13
#define INTEGER_TOKEN 14
#define CHAR_TOKEN    15


#define PV_TOKEN      20 // ;
#define PT_TOKEN      21 // .
#define DP_TOKEN      22 // :
#define VIR_TOKEN     23 // ,
#define PO_TOKEN      24 // (
#define PF_TOKEN      25 // )

#define AFF_TOKEN     30 // :=
#define EQ_TOKEN      31 // =
#define NEQ_TOKEN     32 // <>
#define LT_TOKEN      33 // <
#define LE_TOKEN      34 // <=
#define GT_TOKEN      35 // >
#define GE_TOKEN      36 // >=
#define PLUS_TOKEN    37 // +
#define MOINS_TOKEN   38 // -
#define OR_TOKEN      39 // ||
#define MULT_TOKEN    40 // *
#define DIV_TOKEN     41 // /
#define MOD_TOKEN     42 // %
#define AND_TOKEN     43 // &&

#define ID_TOKEN      50 // Identificateurs (variables)
#define NUM_TOKEN     51 // Nombres

#define EOF_TOKEN     99

#define T_ENTIER 0
#define T_CHAR   1
#define T_ERREUR 2

#endif