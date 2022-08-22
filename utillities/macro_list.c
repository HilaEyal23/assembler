#include "macro_list.h"

void stream_macro(FILE *fp, macroNode *head, char *name){
    macro *macro = find_macro(head, name);
    char *token;
    token = strtok(macro->content, "\t\n");
    while( token != NULL ) {
      fputs(token,fp);
      token = strtok(NULL, "\t\n");
   }
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
        if(!strcmp(currNode->currMacro.name, macroName)) return true;
        currNode = currNode->next;
    }
    return false;
}
