#ifndef MACROLIST_H
#define MACROLIST_H
#include "preprocessor.h"

typedef struct macroNode{
    macro currMacro;
    struct macroNode* next;
}macroNode;

/*
 *this function appends a new node in the end of the linked list. each node contains the macro's content.
 * @param head_ref - a pointer to the list's head. it will be used to find the last node in the list.
 * @param newContent - the data that the new macro contains
 */
void insert_macro(macroNode **head, char *macroName, char *content);


macro find_macro(macroNode *head, char *macroName);

#endif /*MACROLIST_H*/
