#include "utils.h"

void skip_spaces(char **p){
    while((*p)[0] == ' ' || (*p)[0] == TAB) {
        *p += 1;
    }
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

