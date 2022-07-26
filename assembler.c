#include "assembler.h"

int main(int argc, char **argv){
    FILE *fp;
    char filesName[MAX_LINE_LENGTH] = {0};
    int i;

    if(argc == 1){
        printf("no files were given\n");
        exit(0);
    }
    for(i=0; i<argc; i++){
        strcpy(filesName, argv[i]);
        (file_Name_is_valid(filesName))
        fp = fopen(filesName,"r"); /*opening the file according it's name (including file type)*/
        preprocess(fp, filesName);
        return 0;
    }
}



}

