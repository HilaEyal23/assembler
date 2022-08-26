#include "entryAndExtern.h"

/*---entry list functions*/
entry *init_entry_node(entry* next, char *name){
    entry *node = (entry*)malloc(sizeof(entry)*MAX_NAME_LENGTH);

    if(name != NULL){
        strcpy(node->name, name);
    }
    node->next = next;
    return node;
}

void insert_entry(entry* head, char *name){
    entry *temp = head;
    if(!strcmp(head->name, "999")){
        strcpy(head->name, name);
    }
    else{
        while(temp->next){
            temp = temp->next;
        }
        temp->next = init_entry_node(NULL, name);
    }
}
void free_entry_list(entry *head)
{
    entry* temp;
    while(head){
        temp = head;
        head = head->next;
        free(temp);
    }
}

void print_entry_list(entry* head){
    while(head){
        printf("name: %s\n", head->name);
        head = head -> next;
    }
    printf("\n\n");
}




/*---extern list functions---*/

external *init_extern_node(external* next, char *name){
    external *node = (external*)malloc(sizeof(external)*MAX_NAME_LENGTH);

    if(name != NULL){
        strcpy(node->name, name);
    }
    node->next = next;
    return node;
}

void insert_extern(external* head, char *name){
    external *temp = head;
    if(!strcmp(head->name, "999")){
        strcpy(head->name, name);
    }
    else{
        while(temp->next){
            temp = temp->next;
        }
        temp->next = init_extern_node(NULL, name);
    }
}
void free_extern_list(external *head)
{
    external* temp;
    while(head){
        temp = head;
        head = head->next;
        free(temp);
    }
}

void print_extern_list(external* head){
    while(head){
        printf("name: %s\n", head->name);
        head = head -> next;
    }
    printf("\n\n");
}

int find_extern_address(external *head, char *name){
    external *ptr = head;
    while(ptr){
        if(!strcmp(ptr->name, name)) {
            return 1;
        }
	    ptr = ptr->next;
    }
    return NOT_FOUND;
}