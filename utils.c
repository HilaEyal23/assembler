#include "utils.h"

boolean is_register(char *token){
    int i;
    for(i=0; i<REGISTER_AMOUNT; i++){
        if(!strncmp(token, ourRegisters->name, REGISTER_NAME_LEN))
            return true;
    }
    return false;
}
boolean is_int(char *seq){
    if(end_of_line(seq)) return false;
    if(*seq == '+' || *seq == '-'){
        seq++;
        if(!isdigit(*seq++))
            return false;
    }
    while(!end_of_line(seq)){
        if(!isdigit(*seq++))
            return false;
    }
    return true;
}

boolean is_str(char *string)
{
    if(string == NULL) return false;

    if (*string == '"')
        string++;
    else
        return false;

    while (*string && *string != '"') {
        string++;
    }

    if (*string != '"')
        return false;

    string++;
    if (*string != '\0')
        return false;

    return true;
}


int find_idx(char *token, const char *arr[], int len){
    int i;
    for(i=0; i<len; i++){
        if(!strcmp(token, arr[i]))
            return i;
    }
    return NOT_FOUND;
}

int find_cmd(char *token){
    if(strlen(token) != CMD_LENGTH)
        return NOT_FOUND;
    return find_idx(token, commands, CMD_AMOUNT);
}

int find_instruction(char *token)
{
    if(token == NULL || *token != '.') return NOT_FOUND;
    return find_idx(token, instructions, INSTRUCTION_AMOUNT);
}






boolean end_of_line(char *line){
    return line == NULL || *line == '\0' || *line =='\n';
}

int skipEmpty(char *line, int i){
    for(; i < strlen(line); i++)
    {
        if(!(isspace(line[i]) || line[i]==TAB))
            return i;
    }
    return i;
}
char* skipSpaces(char *ch){
    if(!ch)
        return NULL;
    while(isspace(*ch)){
        ch++;
    }
    return ch;
}

boolean toBeSkipped(char line[]){
    int i = 0;
    i = skipEmpty(line, i);
    if(line[i] == '\0' || line[i] == ';' || line[i] == '\n')
        return true;
    return false;
}

void copy_token(char *dest, char *line){
    int i=0;
    if(!dest || !line)
        return;
    while(i<MAX_LINE_LENGTH && !isspace(line[i]) && line[i] != '\0'){
        dest[i] = line[i];
        i++;
    }
    dest[i] = '\0';
}

char *next_token(char *seq){
    int i = 0;
    if (seq == NULL)
        return NULL;
    while(!isspace(seq) && !end_of_line(seq))
        seq++;
    seq = skipSpaces(seq);
    if(end_of_line(seq))
        return NULL;
    return seq;
}







char *create_file_name(char *original, int type)
{
    char *modified = (char *) malloc(strlen(original) + MAX_EXTENSION_LENGTH);
    if(modified == NULL)
    {
        fprintf(stderr, "Dynamic allocation error.");
        exit(ERROR);
    }
    strcpy(modified, original);

    switch (type)
    {
        case FILE_INPUT:
            strcat(modified, ".as");
            break;

        case FILE_OBJECT:
            strcat(modified, ".ob");
            break;

        case FILE_ENTRY:
            strcat(modified, ".ent");
            break;

        case FILE_EXTERN:
            strcat(modified, ".ext");

    }
    return modified;
}

void encode_to_instructions(unsigned int word)
{
    instructions[ic++] = word;
}

int has_error()
{
    return err != NO_ERROR;
}


unsigned int insert_are(unsigned int info, int are)
{
    return (info << BITS_IN_ARE) | are;
}

char *next_list_token(char *dest, char *line)
{
    char *temp = dest;

    if(end_of_line(line))
    {
        dest[0] = '\0';
        return NULL;
    }

    if(isspace(*line))
        line = skip_spaces(line);

    if(*line == ',')
    {
        strcpy(dest, ",");
        return ++line;
    }

    while(!end_of_line(line) && *line != ',' && !isspace(*line))
    {
        *temp = *line;
        temp++;
        line++;
    }
    *temp = '\0';

    return line;
}

char *next_token_string(char *dest, char *line)
{
    char temp[MAX_LINE_LENGTH];
    line = next_list_token(dest, line);
    if(*dest != '"') return line;
    while(!end_of_line(line) && dest[strlen(dest) - 1] != '"')
    {
        line = next_list_token(temp, line);
        if(line) strcat(dest, temp);
    }
    return line;
}

void init_received_line(receivedLine *receivedLine){
    int i;
    receivedLine->cmdIDX = NOT_FOUND;
    receivedLine->errorType = NO_ERROR;
    receivedLine->numOfOperands = NO_OPERANDS;
    for(i=0; i<CMD_LENGTH; i++){
        receivedLine -> operandsValues[0][i] = 0;
        receivedLine -> operandsValues[1][i] = 0;
        receivedLine -> operandsValues[2][i] = 0;
        receivedLine -> operandsValues[3][i] = 0;
        receivedLine -> operandsValues[4][i] = 0;
    }
    receivedLine->entryFlag = off;
    receivedLine->externFlag = off;
    return;
}



