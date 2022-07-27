#import "firstIteration.h"

void first_iteration(FILE *inputFile, char *filesName){
    int DC = 0, IC = 0, isSymbolDef = false;
    char line[MAX_LINE_LENGTH];
    char linesCopy[MAX_LINE_LENGTH];
    char *token;

    FILE *obFile;
    obFile = fopen(strcat(filesName, ".ob"), "w");

    while(fgets(line, MAX_LINE_LENGTH, inputFile)){
        strcpy(linesCopy, line);
        if(!toBeSkipped(line)) {      /*makes sure the line isn't a command or empty*/
            token = strtok(linesCopy, " \t\n");
            if(find_symbol(token))
                isSymbolDef = true;
            if(is_data_ins(token)){
                if(is_label_def(token)){
                    insert_symbol(token); /*should also check validity and incise DC*/
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