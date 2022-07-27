#include "firstIteration.h"

void insert_symbol(symbolNode *head, char symbolName[], int value, int offset, int type){
    symbolNode *newNode = (symbolNode*)malloc(sizeof(symbolNode)); /*inserting new node*/
    symbolNode last = *head; /*creating a pointer that will be in use later*/

    init_symbol(&newNode->currSymbol, symbolName, value, offset, type);
    newNode->next = NULL; /*the new node is going to be the last , so it's next is NULL*/

    if(head->next == NULL){ /*in this case the new node is the first node*/
        head = newNode;
        return;
    }

    while(last.next != NULL){ /*in this case there are already node/s in the list, we look for the last node*/
        last = *last.next;
    }
    last.next = newNode;
    return;
}

symbol* find_symbol(symbolNode *head, char *symbolName){
    symbolNode *currNode = head;
    if(currNode == NULL)
        return NULL;
    while(currNode != NULL){
        if(!strcmp(currNode->currSymbol.name, symbolName))
            return &(currNode->currSymbol);
        currNode = currNode->next;
    }
    return NULL;
}

void init_symbol(symbol *currSymbol, char name[], int value, int offset, int type){
    strcpy(currSymbol->name, name);
    currSymbol->type = type;
    currSymbol->address= 0;
    currSymbol->offset = offset;
    currSymbol->value = value;
}

void free_list(symbolNode *head){
    symbolNode *tmp;
    while(head){
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void print_symbol_list(symbolNode *head){
    symbolNode *ptr = head;
    while(ptr){
        printf("name: %s\n, value: %d\n, offset: %d\n, base: %d\n\n",
               ptr->currSymbol.name, ptr->currSymbol.value, ptr->currSymbol.offset, ptr->currSymbol.address); /*check that out*/
        ptr = ptr->next;
    }
}

int list_length(symbolNode *head){
    symbolNode *ptr = head;
    int i = 0;

    while(ptr){
        i++;
        ptr = ptr->next;
    }
    return i;
}