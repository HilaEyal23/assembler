#include "assembler.h"

int ic, dc;
boolean ef;
boolean was_error;
extern const char base32[32];
extern cmdLine cmdArray[2560];
extern dirLine dirArray[2560];
extern word dirWordArr[2560];
extern word cmdWordArr[2560];
boolean entry_exists, extern_exists;
int cmdCnt;
int dirCnt;



int assembler(int argc, char **argv){
    FILE *fp;
    char amFileName[MAX_LINE_LENGTH];
    char fileName[MAX_LINE_LENGTH];
    int i;
    symbolNode *head;
    entry *entHead;
    external *extHead;

    if(argc == 1){ /*if not even 1 file was given we print error message*/
        printf("no files were given\n");
        exit(1);
    }
    for(i = 1; i < argc; i++){/*we loop over the file names that we gon in argv and handle them*/
        strcpy(fileName, argv[i]);

        fp = fopen(fileName, "r"); /*opens first file with the given name*/
        if(fp != NULL) { 
            printf("************* Started %s assembling process *************\n\n", fileName);
            /*------ pre process-------*/
            preprocess(fp, fileName);
            reset_global_vars();
            strcpy(amFileName, fileName)    ;
            strcat(amFileName, ".am\0");
            fclose(fp);
            /*------first pass-------*/
            fp = fopen(amFileName, "r");
            first_pass(fp, fileName, &head, &entHead, &extHead);
            /*------second pass-------*/
            if (!ef) { 
                rewind(fp);
                second_pass(cmdArray, dirArray, argv[i], head, entHead, extHead);
            }
            free_symbol_list(head);
            free_entry_list(entHead);
            free_extern_list(extHead);
            printf("\n\n************* Finished %s assembling process *************\n\n", fileName);
        }
        else{ /*if this file is unavailable we print an error message*/
            printf("cannot open %s file\n", argv[i]);
        }
        
    }

    return 0;
}



void reset_global_vars(){
    ic = 0;
    dc = 0;
    cmdCnt = 0;
    dirCnt = 0;
    /*err = NO_ERROR;*/
    entry_exists = false;
    extern_exists = false;
}