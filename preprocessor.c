#include "preprocessor.h"


void preprocess(FILE *fp, char *fileName){
    char line[MAX_LINE_LENGTH];
    char lineCopy[MAX_LINE_LENGTH];
    char name[MAX_LINE_LENGTH];
    char amFile[MAX_LINE_LENGTH];
    char *token;
    char *content;
    macroNode *head;
    int macroFlag = false;
    char *p; 
    int i = 1;

    strcpy(amFile,fileName);
    strcat(amFile,".am");
    FILE *preprocessedFile = fopen(amFile, "w");
    head = init_macro_node(NULL, "999","999");
    content = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
    while(fgets(line, MAX_LINE_LENGTH, fp)){
        strcpy(lineCopy, line);
        token = strtok(lineCopy, " \t");
        if(macro_exists(head, token)){
            puts("ho");
            stream_macro(preprocessedFile, head, name);
        }
        else if(!strcmp(token, "macro")){
            macroFlag = true;
            token = strtok(NULL, " \t");
            strcpy(name, token);
        }
        else if(macroFlag){
            i++;
            strcpy(lineCopy, line);
            if(!strncmp(token,"endmacro", 8)){

                macroFlag = false;
                insert_at_end(&head, name, content);
                free(content);
                content = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
                i = 1;
            }
            else{        
                p = (char*)realloc(content, MAX_LINE_LENGTH*sizeof(char)*i); 
                if(p == NULL){ 
                    printf("error with allocation!");
                }
                else content = p;       
                strcat(content, lineCopy);
            }
        }
        else{
            fputs(line, preprocessedFile);
        }
    }
    free(content);
    fclose(preprocessedFile);
    free_macro_list(head);
}

