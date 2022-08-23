#include "symbolList.h"

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

int find_symbol_address(symbolNode *head, char *name){
    symbolNode *ptr = head;
    while(ptr){
        if(!strcmp(ptr->currentNode.name, name)) {
            return ptr->currentNode.address;
        }
	ptr = ptr->next;
    }
    return NOT_FOUND;
}

int find_symbol_type(symbolNode *head, char *name){
    symbolNode *ptr = head;
    while(ptr){
        if(!strcmp(ptr->currentNode.name, name)) {
            return ptr->currentNode.type;
        }
	ptr = ptr->next;
    }
    return NOT_FOUND;
}
