#include "globals.h"
#include "structs.h"
#include "utils.h"
#include "firstPass.h"

void first_pass(FILE *fp, char *fileName);
void second_pass(cmdLine cmdLines[], char *fileName);

extern int ic, dc;
extern int err;
extern boolean was_error;
extern const char base32[32];
extern cmdLine cmdArray[2560];
extern dirLine dirArray[2560];
extern word dirWordArr[2560];
extern word cmdWordArr[2560];
extern boolean entry_exists, extern_exists;

    /*const char base32[32] = {
            '!', '@', '#', '$', '%', '^', '&', '*',
            '<','>', 'a', 'b', 'c','d', 'e', 'f',
            'g','h', 'i', 'j', 'k', 'l', 'm', 'n',
            'o', 'p','q', 'r', 's', 't', 'u', 'v'
    };*/

void reset_global_vars(){
    ic = 0;
    dc = 0;
    err = NO_ERROR;
    entry_exists = false;
    extern_exists = false;
}

int main(int argc, char *argv[]){
    int i;
    char *input_filename;
    FILE *fp;

    for(i = 1; i < argc; i++)
    {
        input_filename = create_file_name(argv[i], FILE_INPUT); /* Appending .as to filename */
        fp = fopen(input_filename, "r");
        if(fp != NULL) { /* If file exists */
            printf("************* Started %s assembling process *************\n\n", input_filename);

            reset_global_vars();
            first_pass(fp, argv[i]);

            if (!was_error) { /* procceed to second pass */
                rewind(fp);
                second_pass(cmdArray, argv[i]);
            }

            printf("\n\n************* Finished %s assembling process *************\n\n", input_filename);
        }
        /*else print_error(CANNOT_OPEN_FILE);*/
        free(input_filename);
    }

    return 0;
}







/*int main(int argc, char **argv){
    FILE *fp;
    char fileName[MAX_LINE_LENGTH];
    if(argc == 1){
        printf("no files were given!\n");
        exit(1);
    }
    strcpy(fileName, argv[1]);
    fp = fopen(fileName, "r");
    first_pass(fp, fileName);
    second_pass(cmdArray);
    return 0;
}*/
