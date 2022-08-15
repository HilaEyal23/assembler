#ifndef _STRUCTS_H
#define _STRUCTS_H

#include "globals.h"

typedef struct structLabels * labelPtr;

typedef struct label{
    char name[MAX_NAME_LENGTH];
    unsigned int address;
    boolean external;
    boolean isActionStatement;
    boolean entry;
    labelPtr next;
}label;

typedef struct ext * extPtr;
typedef struct ext {
    char name[MAX_NAME_LENGTH];
    unsigned int address;
    extPtr next;
    extPtr prev;
} ext;

typedef struct word{
    unsigned int opcode[5];
    unsigned int src[3];
    unsigned int dst[3];
    unsigned int ARE[3];
}word;

typedef struct receivedLine{
    char line[MAX_LINE_LENGTH];
    int cmdIDX;
    int errorType;
    char operandsValues[OPERAND_TYPES_AMOUNT][MAX_NUM_OF_OPERANDS];
    int numOfOperands;
    flag entryFlag;
    flag externFlag;
    /*int opcode;
    int src_operand;
    int dst_operand;
    int offset;*/
}receivedLine;

typedef struct cmd{
    char name[CMD_LENGTH];
    int cmdCode;
    int numOfOperands;
}cmd;

cmd ourCmd[] = {
        {"mov", MOV, 2},
        {"cmp", CMP, 2},
        {"add", ADD, 2},
        {"sub", SUB, 2},
        {"lea", LEA, 2},

        {"not", NOT, 1},
        {"clr", CLR, 1},
        {"inc", INC, 1},
        {"dec", DEC, 1},
        {"jmp", JMP, 1},
        {"bne", BNE, 1},
        {"get", GET, 1},
        {"prn", PRN, 1},
        {"jsr", JSR, 1},

        {"rst", RST, 0},
        {"hlt", HLT, 0},
};

typedef struct Register{
    char *name;
    int num;
    int data;
}Register;

Register ourRegisters[] = {
        {"r0", 0, 0},
        {"r1", 1, 0},
        {"r2", 2, 0},
        {"r3", 3, 0},
        {"r4", 4, 0},
        {"r5", 5, 0},
        {"r6", 6, 0},
        {"r7", 7, 0}
};

const char base32[32] = {
        '!', '@', '#', '$', '%', '^', '&', '*',
        '<','>', 'a', 'b', 'c','d', 'e', 'f',
        'g','h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p','q', 'r', 's', 't', 'u', 'v'
};

const char *instructions[] = {
        ".data", ".string", ".struct", ".entry", ".extern"
};

/*typedef struct symbolNode{
    symbol currSymbol;
    struct symbolNode *next;
}symbolNode;*/

typedef struct wordNode{
    word currWord;
    struct wordNode *next;
}wordNode;


#endif /*_STRUCTS_H*/
