#include "symbolList.h"

symbolNode* init_symbol(char name[], unsigned int value, unsigned long addre#include "symbolList.h"



symbolNode *init_symbol_node(symbolNode* next, char *name, int address, int type){

    symbolNode *node = (symbolNode*)malloc(sizeof(symbolNode)*MAX_NAME_LENGTH);



    if(name != NULL){

        node->currentNode.name = (char*)malloc(MAX_NAME_LENGTH*sizeof(char));

        strcpy(node->currentNode.name, name);

    }

    node->currentNode.address = address;

    node->currentNode.type = type;

    node->next = next;

    return node;

}



void insert_symbol(symbolNode* head, char *name, int address, int type){

    symbolNode *temp = head;

    if(!strcmp(head->currentNode.name, "999")){

        strcpy(head->currentNode.name, name);

        head->currentNode.address = address;

        head->currentNode.type = type;

    }

    else{

        while(temp->next){

            temp = temp->next;

        }

        temp->next = init_symbol_node(NULL, name, address, type);

    }

}



void print_symbol_list(symbolNode* head){

    while(head){

        printf("name: %s address: %d type: %d\n", head->currentNode.name, head->currentNode.address, head->currentNode.type);

        head = head -> next;

    }

    printf("\n\n");

}



int symbol_exists(symbolNode *head, char *name){

    symbolNode *currentNode = head;

    while(currentNode != NULL){

        if(!strcmp(currentNode->currentNode.name, name)) return true;

        currentNode = currentNode->next;

    }

    return false;

}



int find_symbol_value(symbolNode *head, char *name){

    symbolNode *ptr = head;

    while(ptr){

        if(!strcmp(ptr->currentNode.name, name)) {

            return ptr->currentNode.address;

        }

    }

    return NOT_FOUND;

}ss, symbolType type, int offset){
    symbolNode *newNode = (symbolNode*)malloc(sizeof(symbolNode*));

    if(name)
        strcpy(newNode->currSymbol.name, name);
    newNode->currSymbol.value = value;
    newNode->currSymbol.address = address;
    newNode->currSymbol.type = type;
    newNode->currSymbol.offset = offset;
    newNode->next = NULL;

    return newNode;
}

void free_symbol_list(symbolNode *head){
    symbolNode *tmp;
    while(head){
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void insert_symbol(symbolNode **head, symbolNode *newNode){
    symbolNode *last = *head;
    int i=0;

    while(last->next){
        last = last->next;
    }
    last->next = newNode;
}

int symbol_list_length(symbolNode *head){
    symbolNode *ptr = head;
    int i = 0;

    while(ptr){
        i++;
        ptr = ptr->next;
    }
    return i;
}

int is_symbol_defined(symbolNode *head, char name[]){
    while(head){
        if(!strncmp(head->currSymbol.name, name, MAX_NAME_LENGTH))
            return true;
        head = head->next;
    }
    return false;
}

void print_symbol_list(symbolNode *head){
    symbolNode *ptr = head;
    while(ptr){
        printf("name: %s\n, value: %d\n, address: %lu\n, offset: %d\n\n",
               ptr->currSymbol.name, ptr->currSymbol.value, ptr->currSymbol.address, ptr->currSymbol.offset); /*check that out*/
        ptr = ptr->next;
    }
}

void update_entry(symbolNode *head, char name[]){
    do
    {
        if (!strcmp(head->currSymbol.name, name)){
            head->currSymbol.type = ENTRY_SYMBOL; /*to be checked*/
            return;
        }
    } while ((head = head->next));
}






























//void insert_symbol(symbolNode *head, char symbolName[], int value, int offset, int type){
//    symbolNode *newNode = (symbolNode*)malloc(sizeof(symbolNode)); /*inserting new node*/
//    symbolNode last = *head; /*creating a pointer that will be in use later*/
//
//    init_symbol(&newNode->currSymbol, symbolName, value, offset, type);
//    newNode->next = NULL; /*the new node is going to be the last , so it's next is NULL*/
//
//    if(head->next == NULL){ /*in this case the new node is the first node*/
//        head = newNode;
//        return;
//    }
//
//    while(last.next != NULL){ /*in this case there are already node/s in the list, we look for the last node*/
//        last = *last.next;
//    }
//    last.next = newNode;
//    return;
//}

symbol* find_symbol(symbolNode *head, char *symbolName) {
    symbolNode *currNode = head;
    if (currNode == NULL)
        return NULL;
    while (currNode != NULL) {
        if (!strcmp(currNode->currSymbol.name, symbolName))
            return &(currNode->currSymbol);
        currNode = currNode->next;
    }
    return NULL;
}





