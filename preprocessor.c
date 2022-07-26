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

void preprocess(FILE *inputFile, char *filesName){
    char line[MAX_LINE_LENGTH];
    char linesCopy[MAX_LINE_LENGTH];
    char *token, *macroContent;
    char macroName[MAX_LINE_LENGTH];
    macroNode head;
    int isMacroDef = false;

    FILE *amFile;
    amFile = fopen(strcat(filesName, ".am"), "w");
    macroContent = (char*) malloc(MAX_LINE_LENGTH);
    head.next = NULL;

    while(fgets(line, MAX_LINE_LENGTH, inputFile)){
        strcpy(linesCopy, line);
        if(!toBeSkipped(line)){      /*makes sure the line isn't a command or empty*/
            token = strtok(linesCopy, " \t\n");
            if(!find_macro(&head, token)){
                if(!strcmp(token, "macro")){
                    isMacroDef = true;
                    token = strtok(NULL, " \t\n");
                    strcpy(macroName, token);
                }
                while(isMacroDef){
                    fgets(line, MAX_LINE_LENGTH, inputFile);
                    strcpy(linesCopy, line);
                    token = strtok(linesCopy, " \t\n");
                    if(!strcmp(token, "endmacro")){
                        insert_macro(&head, macroName, macroContent); /*to be fixed*/
                        isMacroDef = false;
                        continue;
                    }
                    else{
                        printf("macro content\n");
                        strcat(macroContent, line);
                        macroContent = (char*)realloc(linesCopy, sizeof(MAX_LINE_LENGTH)); /*to be fixed*/
                        if(!macroContent){
                            printf("error with allocation\n");
                            exit(0);
                        }
                    }
                }
            }
            else{
                fputs(find_macro(&head, token)->content ,amFile);
                continue;
            }
        }
        else{
            fputs(line, amFile);
            continue;
        }
    }
    free(macroContent);
    fclose(amFile);
    return;
}
