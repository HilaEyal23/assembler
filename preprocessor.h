#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "utils.h"
/*#include "macroList.h"*/

#define MAX_LINE_LENGTH 81

typedef struct macro{
    char* name;
    char* content;
}macro;

typedef struct macroNode{
    macro currMacro;
    struct macroNode* next;
}macroNode;

/*
 *
 */
void preprocess(FILE *inputFile, char *fileName);
/*int is_name_valid(char *name);*/
void insert_macro(macroNode *head, char *macroName, char *content);
macro* find_macro(macroNode *head, char *macroName);

#endif /*PREPROCESSOR_H*/