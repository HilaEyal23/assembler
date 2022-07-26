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

/*void skipEmpty(char line[]){
    int cnt = 0, i = 0;
    int strLen = strlen(line);
    while(i<strLen){
        if(line[i] != ' ' && line[i] != TAB)
            break;
        i++;
        cnt++;
    }
    memmove(line, line + cnt, strlen(line));
}*/
/*int toBeSkipped(char line[]){
    skipEmpty(line);
    if(line[0] == '\0' || line[0] == ';' || line[0] == '\n')
        return true;
    return false;
}*/

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
