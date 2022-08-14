#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "utils.h"
/*#include "macroList.h"*/
/*#include "../utillities/macros.h"*/

#define MAX_LINE_LENGTH 81

typedef struct macro{
    char *name;
    char *content;
}macro;

typedef struct macroNode{
    macro currMacro;
    struct macroNode *next;
}macroNode;

/*
 *
 
 */
 void insert_at_end(macroNode** head, char *name, char* content);
 void print_macro_list(macroNode* head);
 macroNode* init_macro_node(macroNode* next, char* name, char* content);
 int macro_exists(macroNode *head, char *macroName);
 void old_preprocessor(FILE *inputFile, char *fileName);
void preprocess(FILE *inputFile, char *fileName);
/*int is_name_valid(char *name);*/
void insert_macro(macroNode *head, char macroName[], char **content);
macro* find_macro(macroNode *head, char *macroName);
void swich_name_with_content(macroNode *head, char macroName[], FILE *amFile);

#endif /*PREPROCESSOR_H*/
