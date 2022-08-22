#ifndef _SYMBOLLIST_H
#define _SYMBOLLIST_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "globals.h"

#define MAX_NAME_LENGTH 31
#define MAX_LINE_LENGTH 81

typedef struct symbol{
    char *name;
    int address;
    int type;
}symbol;

typedef struct symbolNode{
    symbol currentNode;
    struct symbolNode *next;
}symbolNode;

symbolNode *init_symbol_node(symbolNode* next, char *name, int address, int type);
void insert_symbol(symbolNode* head, char *name, int address, int type);
void print_symbol_list(symbolNode* head);
int symbol_exists(symbolNode *head, char *name);
int find_symbol_value(symbolNode *head, char *name);



#endif /*_SYMBOLLIST_H*/
