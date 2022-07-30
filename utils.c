#include "utils.h"

int is_cmd(char str[]){
    int i;
    for(i=0; i<CMD_AMOUNT; i++){
        if(!strcmp(str,ourCmd[i].name)){
            return true;
        }
    }
    return false;
}

int is_int(char s[]){
    int i;
    for(i=0; i<strlen(s);i++ ){
        if(!isdigit(s[i]))
            return false;
    }
    return true;
}

int skipEmpty(char *line, int i){
    for(; i < strlen(line); i++)
    {
        if(!(isspace(line[i]) || line[i]==TAB))
            return i;
    }
    return i;
}

int toBeSkipped(char line[]){
    int i = 0;
    i = skipEmpty(line, i);
    if(line[i] == '\0' || line[i] == ';' || line[i] == '\n')
        return true;
    return false;
}
