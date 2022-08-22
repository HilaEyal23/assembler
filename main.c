#include "globals.h"
#include "structs.h"
#include "utils.h"
#include "firstPass.h"

void first_pass(FILE *fp, char *fileName);
void second_pass(cmdLine cmdLines[], char *fileName);

extern int ic, dc;
extern int err;
boolean was_error;
extern const char base32[32];
extern cmdLine cmdArray[2560];
extern dirLine dirArray[2560];
extern word dirWordArr[2560];
extern word cmdWordArr[2560];
boolean entry_exists, extern_exists;


void reset_global_vars(){
    ic = 0;
    dc = 0;
    /*err = NO_ERROR;*/
    entry_exists = false;
    extern_exists = false;
}



int main(int argc, char **argv){
    FILE *fp;
    char fileName[MAX_LINE_LENGTH];
    int i;

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
	reset_global_vars();
        first_pass(fp, argv[i]);
	if (!was_error) { 
                rewind(fp);
                second_pass(cmdArray, argv[i]);
            }

        printf("\n\n************* Finished %s assembling process *************\n\n", fileName);
        }
	else{
	    printf("cannot open %s file\n", argv[i]);
	}
        
    }

    return 0;
}









