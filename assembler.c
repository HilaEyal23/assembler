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

    if(argc == 1){
        printf("no files were given\n");
        exit(1);
    }
    for(i = 1; i < argc; i++)
    {
        strcpy(fileName, argv[i]);

        fp = fopen(fileName, "r");
        if(fp != NULL) { 
            printf("************* Started %s assembling process *************\n\n", fileName);

            preprocess(fp, fileName);
            reset_global_vars();

            strcpy(amFileName, fileName);
            strcat(amFileName, ".am\0");

            fclose(fp);
            fp = fopen(amFileName, "r");
            /*fp = fopen("text1.am", "r");*/
            first_pass(fp, fileName, &head);
            if (!was_error) { 
                rewind(fp);
                second_pass(cmdArray, dirArray, argv[i], head);
            }
            free_symbol_list(head);
            printf("\n\n************* Finished %s assembling process *************\n\n", fileName);
        }
        else{
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