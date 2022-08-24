#ifndef MACRO_LIST_H
#define MACRO_LIST_H
#include "macros.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "utils.h"

typedef struct macroNode{
    macro currMacro;
    struct macroNode *next;
}macroNode;


#define MAX_LINE_LENGTH 81
void free_macro_list(macroNode *head);
macro* find_macro(macroNode *head, char *macroName);
void stream_macro(FILE *fp, macroNode *head, char *name);
 void insert_at_end(macroNode** head, char *name, char* content);
 void print_macro_list(macroNode* head);
 macroNode* init_macro_node(macroNode* next, char* name, char* content);
 int macro_exists(macroNode *head, char *macroName);



#endif
