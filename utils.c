#include "utils.h"

/*int is_cmd(char str[]){
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
}*/

void skip_spaces(char **p){
    while((*p)[0] == ' ' || (*p)[0] == TAB) {
        *p += 1;
    }
}

int toBeSkipped(char line[]){
    return false;
}

int space_line(char *line){
    int i = 0;
    skip_spaces(&line);
    if(line[i] =='\n' || line[i] == '\0') return true;
    return false;
}

int comment_line(char *line){
    int i = 0;
    skip_spaces(&line);
    if(line[i] ==';') return true;
    return false;
}

