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

/**/

typedef struct Register{
    char *name;
    int num;
}Register;


/*
const char base32[32] = {
        '!', '@', '#', '$', '%', '^', '&', '*',
        '<','>', 'a', 'b', 'c','d', 'e', 'f',
        'g','h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p','q', 'r', 's', 't', 'u', 'v'
};*/


#endif /*_STRUCTS_H*/

