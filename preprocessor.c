#include "preprocessor.h"

int main(int argc, char **argv){
    FILE *fp;
    char filesName[MAX_LINE_LENGTH] = {0};

    if(argc == 1){
        printf("no files were given\n");
        exit(0);
    }
    strcpy(filesName, argv[1]);
    fp = fopen(filesName,"r"); /*opening the file according it's name (including file type)*/
    preprocess(fp, filesName);
    return 0;
}

void preprocess(FILE *fp, char *fileName){
    char line[MAX_LINE_LENGTH];
    char lineCopy[MAX_LINE_LENGTH];
    char name[MAX_LINE_LENGTH];
    char *token;
    char *content;
    macroNode *head;
    int macroFlag = false;
    char *p; 
    int i = 0;

    head = init_macro_node(NULL, "999","999");
    FILE *preprocessedFile = fopen(strcat(fileName, ".am"), "w");
    content = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));

    while(fgets(line, MAX_LINE_LENGTH, fp)){
        strcpy(lineCopy, line);
        token = strtok(lineCopy, " \t\n");
        
        puts(token);
        if(macro_exists(head, token)){
            puts("hi");
            stream_macro(preprocessedFile, head, token);
        }
        else if(!strncmp(token, "macro", 5)){
            macroFlag = true;
            token = strtok(NULL, " \t\n");
            strcpy(name, token);
        }
        else if(macroFlag){
            i++;
            strcpy(lineCopy, line);
            if(!strncmp(token,"endmacro", 8)){
                macroFlag = false;
                insert_at_end(&head, name, content);
                print_macro_list(head);
                content = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
                i = 1;
            }
            else{        
                p = (char*)realloc(content, MAX_LINE_LENGTH*sizeof(char)*i);  
                if(p == NULL) printf("error with allocation!");
                else content = p;         
                strcat(content, lineCopy);
            }
        }
        else{
            fputs(line, preprocessedFile);
        }
    }
    /*end_of_file();*/
}

