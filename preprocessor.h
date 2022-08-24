#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "utils.h"
#include "macro_list.h"





/*
 *
 
 */
 
 void old_preprocessor(FILE *inputFile, char *fileName);
void preprocess(FILE *inputFile, char *fileName);
/*int is_name_valid(char *name);*/
void insert_macro(macroNode *head, char macroName[], char **content);

void swich_name_with_content(macroNode *head, char macroName[], FILE *amFile);

#endif /*PREPROCESSOR_H*/
