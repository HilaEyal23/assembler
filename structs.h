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
    char operands[20][MAX_NAME_LENGTH];
	int operand_cnt;
    int lineNum;
}dirLine;


#endif /*_STRUCTS_H*/

