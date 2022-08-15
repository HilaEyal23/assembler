#ifndef SYMBOLLIST_H
#define SYMBOLLIST_H
#include "utils.h"

typedef enum symbolType{NO_TYPE = -1, CODE_SYMBOL, DATA_SYMBOL, EXTERNAL_SYMBOL, ENTRY_SYMBOL, REFERENCE_SYMBOL} symbolType;

typedef struct symbol{
    char name[MAX_NAME_LENGTH];
    unsigned int value;
    unsigned long address;
    symbolType type;
    int offset;
}symbol;

typedef struct symbolNode{
    symbol currSymbol;
    struct symbolNode *next;
}symbolNode;


symbolNode* init_symbol(char name[], unsigned int value, unsigned long address, int offset, int type); //
void free_symbol_list(symbolNode *head); //
void print_symbol_list(symbolNode *head); //
int symbol_list_length(symbolNode *head); //
void update_entry(symbolNode *head, char name[]); //
void insert_symbol(symbolNode **head, symbolNode *newNode);//
int is_symbol_defined(symbolNode *head, char name[]); //
symbol* find_symbol(symbolNode *head, char *symbolName);


/* Functions of symbols table */
labelPtr add_label(labelPtr *hptr, char *name, unsigned int address, boolean external, ...);
int delete_label(labelPtr *hptr, char *name);
void free_labels(labelPtr *hptr);
void offset_addresses(labelPtr label, int num, boolean is_data);
unsigned int get_label_address(labelPtr h, char *name);
labelPtr get_label(labelPtr h, char *name);
boolean is_existing_label(labelPtr h, char *name);
boolean is_external_label(labelPtr h, char *name);
int make_entry(labelPtr h, char *name);
void print_labels(labelPtr h);

#endif /*SYMBOLLIST_H*/
