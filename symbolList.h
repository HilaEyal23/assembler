#ifndef SYMBOLLIST_H
#define SYMBOLLIST_H

typedef struct symbolNode{
    char *symbol;
    struct symbolNode* next;
}symbolNode;

#endif /*SYMBOLLIST_H*/
