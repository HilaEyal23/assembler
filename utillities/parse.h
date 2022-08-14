#ifndef _PARSE_H
#define _PARSE_H
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 81
#define MAX_OPERAND_TYPE 5
#define MAX_NUM_OF_OPERANDS 2
#define CMD_AMOUNT 16
#define CMD_LENGTH 4

#define true 1
#define false 0
/*#define NOT_FOUND -1*/
#define LAST_CHAR '\0'
#define DEFAULT_VAL '0'

typedef struct receivedLine{
    char line[MAX_LINE_LENGTH];
    int cmdIDX;
    int errorType;
    char operandsValues[MAX_OPERAND_TYPE][MAX_NUM_OF_OPERANDS];
    int numOfOperands;
    int opcode;
    int src_operand;
    int dst_operand;
    int A_R_E;
    int numOfWords;
}receivedLine;

typedef struct cmd{
    char name[CMD_LENGTH];
    int numOfOperands;
    int cmdCode;
}cmd;

typedef enum operandType{NO_OPERAND = -1, INTEGER, LABEL, REGISTER, STRING, STRUCT, DATA} operandType;
enum error{NO_ERROR, UND_CMD_NAME, EXTRANEOUS_TEXT, MULTIPLE_CON_COMMAS,ILLEGAL_COMMA, MISS_COMMA, MISS_PAR, UND_REGISTER_NAME, NOT_INT, NOT_LIST};
enum commandIdx{NOT_FOUND = -1, MOV, CMP, ADD, SUB, NOT, CLR, LEA, INC, DEC, IMP, BNE, GET, PRN, JSR, RST, HLT};

cmd ourCmd[] = {
        {"mov", 2, 0},
        {"cmp", 2, 1},
        {"add", 2, 2},
        {"sub", 2, 3},
        {"lea", 2, 6},

        {"not", 1, 4},
        {"clr", 1, 5},
        {"inc", 1, 7},
        {"dec", 1, 8},
        {"jmp", 1, 9},
        {"bne", 1, 10},
        {"get", 1, 11},
        {"prn", 1, 12},
        {"jsr", 1, 13},

        {"trs", 0, 14},
        {"hlt", 0, 15},
};

void init_line(receivedLine *receivedLine);
void  parse_input(FILE *ptrFile);
void get_input(receivedLine *receivedLine);

typedef struct reg{
    char *name;
    int data;
}reg;

reg ourRegisters[] = {
        {"r0", 0},
        {"r1", 0},
        {"r2", 0},
        {"r3", 0},
        {"r4", 0},
        {"r5", 0},
        {"r6", 0},
        {"r7", 0}
};

#endif /*_PARSE_H*/
