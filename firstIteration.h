#ifndef FIRSTITERATION_H
#define FIRSTITERATION_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "utils.h"

typedef enum symbolType{NO_TYPE = -1, CODE_SYMBOL, DATA_SYMBOL, EXTERNAL_SYMBOL, ENTRY_SYMBOL, REFERENCE_SYMBOL} symbolType;

typedef struct symbol{
    char name[MAX_NAME_LENGTH];
    char label[MAX_NAME_LENGTH];
    long address;
    symbolType type;
    unsigned int offset;
    int value;
}symbol;

typedef struct symbolNode{
    symbol currSymbol;
    struct symbolNode *next;
}symbolNode;

int is_data_ins();
int errors_found();
int update_symbols_list();
int is_label_def();
int is_ext_or_ent();
int is_ext();
int is_symbol_def();
void insert_symbol(symbolNode *head, char symbolName[], int value, int offset, int type);
symbol* find_symbol(symbolNode *head, char *symbolName);

void init_symbol(symbol *currSymbol, char name[], int value, int offset, int type);
void free_list(symbolNode *head);
void print_symbol_list(symbolNode *head);
int list_length(symbolNode *head);



#endif /*FIRSTITERATION_H*/
