#include "preprocessor.h"

void insert_macro(macroNode *head, char *macroName, char *content){
    macroNode *newNode = (macroNode*)malloc(sizeof(macroNode)); /*inserting new node*/
    macroNode last = *head; /*creating a pointer that will be in use later*/

    strcpy(newNode->currMacro.name, macroName);
    strcpy(newNode->currMacro.content, content);
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

macro* find_macro(macroNode *head, char *macroName){
    macroNode *currNode = head;
    if(currNode == NULL)
        return NULL;
    while(currNode != NULL){
        if(!strcmp(currNode->currMacro.name, macroName))
            return &(currNode->currMacro);
        currNode = currNode->next;
    }
    return NULL;
}

void swich_name_with_content(macroNode *head, char macroName[], FILE *amFile){
    char content[MAX_LINE_LENGTH] = {0};
    char *ptr = find_macro(head, macroName)->content;

    while(ptr){
        strncpy(content, ptr, MAX_LINE_LENGTH);
        ptr = ptr + MAX_LINE_LENGTH;
        fprintf(amFile, "%s", content);
    }
}

