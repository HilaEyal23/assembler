#ifndef _STRUCTS_H
#define _STRUCTS_H

#include "globals.h"

#define BITS_IN_WORD 10
#define CMD_LENGTH 4

typedef struct word{
    unsigned int bits : BITS_IN_WORD;
} word;

typedef struct cmdLine{
    int cmdIDX;
    char src[MAX_NAME_LENGTH];
    int srcType;
    char dest[MAX_NAME_LENGTH];
    int destType;
    int numOfOperands;
    int lineNum;
}cmdLine;



typedef struct dirLine{
    int dirType;
    char *operand;
    int lineNum;
}dirLine;



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

        {"rts", RTS, 0},
        {"hlt", HLT, 0},
};


typedef struct Register{
    char *name;
    int num;
}Register;

Register ourRegisters[] = {

        {"r0", 0},

        {"r1", 1},

        {"r2", 2},

        {"r3", 3},

        {"r4", 4},

        {"r5", 5},

        {"r6", 6},

        {"r7", 7}

};

/*
const char base32[32] = {

        '!', '@', '#', '$', '%', '^', '&', '*',

        '<','>', 'a', 'b', 'c','d', 'e', 'f',

        'g','h', 'i', 'j', 'k', 'l', 'm', 'n',

        'o', 'p','q', 'r', 's', 't', 'u', 'v'

};*/



#endif /*_STRUCTS_H*/
