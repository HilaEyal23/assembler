#ifndef LIST_H_
#define LIST_H_
#include "globals.h"



typedef struct entry{
    char name[MAX_NAME_LENGTH];
    struct entry *next;
} entry;

typedef struct external{
    char name[MAX_NAME_LENGTH];
    struct external *next;
} external;

/*entry list functions*/
entry *init_entry_node(entry* next, char *name);
void insert_entry(entry* head, char *name);
void free_entry_list(entry *head);
void print_entry_list(entry* head);

/*extern list functions*/
external *init_extern_node(external *next, char *name);
void insert_extern(external* head, char *name);
void free_extern_list(external *head);
void print_extern_list(external* head);
int find_extern_address(external *head, char *name);




#endif