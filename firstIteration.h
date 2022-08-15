#ifndef FIRSTITERATION_H
#define FIRSTITERATION_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "utils.h"

typedef struct word{
    int word[MAX_WORD_LENGTH];
}word;

typedef struct wordNode{
    word currWord;
    struct wordNode *next;
}wordNode;

int is_data_ins();
int errors_found();
int update_symbols_list();
int is_label_def();
int is_ext_or_ent();
int is_ext();
int is_symbol_def();



#endif /*FIRSTITERATION_H*/
