#include "preprocessor.h"

void insert_macro(macroNode *head, char macroName[], char **content){
    macroNode *newNode = (macroNode*)malloc(sizeof(macroNode)); /*inserting new node*/
    macroNode last = *head; /*creating a pointer that will be in use later*/

    newNode->currMacro.name = macroName;
    newNode->currMacro.content = *content;
    newNode->next = NULL; /*the new node is going to be the last , so it's next is NULL*/
    puts(newNode->currMacro.name);
    puts(newNode->currMacro.content);
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
void insert_at_end(macroNode** head, char *name, char* content)
{
    macroNode *temp = *head;
    
    if (!strcmp(temp->currMacro.name, "999") && !strcmp(temp->currMacro.content, "999"))
    {
        strcpy(temp->currMacro.name, name);
        strcpy(temp->currMacro.content, content);
        return;
    }
    while (temp->next)
    {
        temp = temp->next;
    }
    temp->next = init_macro_node(NULL,name,content);
}

void print_macro_list(macroNode* head)
{
    while (head)
    {
        printf("Name: %s\n{\n\t%s\n}\n", head->currMacro.name, head->currMacro.content);
        head = head->next;
    }
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

macroNode* init_macro_node(macroNode* next, char* name, char* content)
{
    macroNode* node = (macroNode*)malloc(sizeof(macroNode));
    if(content != NULL){
        node->currMacro.content = (char*)malloc(MAX_LINE_LENGTH*sizeof(char));
        strcpy(node->currMacro.content, content);
    }

    if(name != NULL){
        node->currMacro.name = (char*)malloc(MAX_LINE_LENGTH*sizeof(char));
        strcpy(node->currMacro.name, name);    
    }

    node->next = next;
    return node;
}

int macro_exists(macroNode *head, char *macroName){
    macroNode *currNode = head;
    while(currNode != NULL){
        if(!strncmp(currNode->currMacro.name, macroName,1)) return true;
        currNode = currNode->next;
    }
    return false;
}

void swich_name_with_content(macroNode *head, char macroName[], FILE *amFile){
    char content[MAX_LINE_LENGTH] = {'\0'};
    char *ptr = find_macro(head, macroName)->content;

    while(ptr){
        strncpy(content, ptr, MAX_LINE_LENGTH);
        ptr = ptr + MAX_LINE_LENGTH;
        fprintf(amFile, "%s", content);
    }
}

