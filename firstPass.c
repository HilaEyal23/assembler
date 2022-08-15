#include "firstPass.h"
int IC, DC;

void firstPass(FILE *filePtr, symbolNode *symbolHead){
    receivedLine *receviedLine;
    char line[MAX_LINE_LENGTH];
    char linesCopy[MAX_LINE_LENGTH];
    char *token, *word;
    symbolNode *label;
    int isSymbolDef = false;

    DC = 0, IC = 100; /*to be checked*/

    while(fgets(line, MAX_LINE_LENGTH, filePtr)){
        strcpy(receviedLine->line, line);
        if(!toBeSkipped(receviedLine->line)) {      /*makes sure the line isn't a command or empty*/
            token = strtok(linesCopy, ":");
            if (token!=NULL){
                if(find_symbol(symbolHead, token)){
                    /*to be continued*/
                }
                else{
                    isSymbolDef = true;
                }
            }
            token = strtok(linesCopy, " \t\n");
            if(find_symbol(head, token))
                isSymbolDef = true;
            if(is_data_ins(token)){
                if(is_label_def(token)){
                    insert_symbol(head,token,val, off, type); /*should also check validity and incise DC*/
                }
                /*line 7*/
            }
            else{
                if(is_ext_or_ent(token)){
                    if(is_ext(token)){
                        /*line 9*/
                        continue;
                    }
                }
                else{
                    if(is_symbol_def(token)){
                        insert_symbol(token); /*should also check validity. symbol from code type when its value is IC*/
                    }
                }
            }
            if(errors_found(file)){
                exit(0); /*what does "stop" mean?*/
            }
            update_symbols_list();
            return;
        }
        else{
            fputs(line, obFile);
            continue;
        }
    }
}

void get_operands_type(receivedLine *receivedLine){
    char *token;
    token = strtok(token, "#");
    if(token){
        strcpy(receivedLine->line, token);
        receivedLine->operandsValues[];
        return;
    }
    token = strtok(token, )
}
