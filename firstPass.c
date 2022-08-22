#include "firstPass.h"

int main(int argc, char **argv){
    FILE *fp;
    char fileName[MAX_LINE_LENGTH];
    if(argc == 1){
        printf("no files were given!\n");
        exit(1);
    }
    strcpy(fileName, argv[1]);
    fp = fopen(fileName, "r");
    first_pass(fp, fileName);
    return 0;
}
char directives[5][8] = {".data", ".string", ".struct", ".entry", ".extern"};
int ef = 0;
cmdLine cmdArray[40];
int cmd_cnt = 0;
dirLine dirArray[40];
int dir_cnt = 0;

void first_pass(FILE *fp, char *fileName){
    int lineNumber = 1;
    char line[MAX_LINE_LENGTH];
    char linesCopy[MAX_LINE_LENGTH];
    char label[MAX_NAME_LENGTH];
    /*char command[MAX_NAME_LENGTH];*/
    char *token;
    int labelFlag = 0;
    int directFlag = 0;

    int directType;
    int args[2];
    int IC = 101;
    int DC = 1;


    symbolNode *head = init_symbol_node(NULL, "999", 0, -1);
    while(fgets(line, MAX_LINE_LENGTH, fp)){
        strcpy(linesCopy, line);
        if(!to_be_skipped(line)){
            validate_input_form(line, lineNumber);
            token = strtok(line, " \t\n");
            if(is_label(token, lineNumber)){
                /*strcpy(label, token);*/
                copy_label_name(label, token);
                if(symbol_exists(head ,label)){
                    printf("label is already defined!\n");
                }
                else{
                    labelFlag = 1;
                }
            }
            token = strtok(NULL, " \t\n");
            if(is_direct(token, lineNumber)){
                directFlag = 1;
                if(validate_direct_form(linesCopy, labelFlag, lineNumber)){/*create this function*/
                    directType = get_direct_type(token, lineNumber);
                }
            }
            if(directFlag && labelFlag){
                insert_symbol(head, label, DC, directType);
                DC++;
            }/*if it is not direct then it is code*/
            else if(validate_instruction_form(linesCopy, labelFlag, lineNumber, &args[0], &args[1])){
                if(labelFlag){
                    insert_symbol(head, label, IC, CODE);
                    IC += find_L(args[0], args[1])+1;
                }
            }
        }
        labelFlag = 0;
        directFlag = 0;
        lineNumber++;
        /*print_symbol_list(head);*/
    }
    print_symbol_list(head);
    print_cmdArray();
}


int validate_input_form(char *line, int lineNumber){/*fix this function!!!*/
    char input[MAX_LINE_LENGTH];
    char *token;
    int comma_cnt = 0;
    int tokens_cnt = 0;
    char *p = input;
    strcpy(input, line);
    skip_label(&p); /*skiping the label is there is one :)*/
    token = strtok(p, " \t\n");
    if(token[0] == ','){ /*unvaild comma check ar start/after label*/
        printf("%d: illegal comma\n", lineNumber);
        ef = true;
    }
    /*while(token != NULL && token[0] != '\n'){
        token = strtok(NULL, " \t\n");
        if(token[0] != ','){
            printf("%d: missing comma\n", lineNumber);
            ef = 1;
        }
    }*/

    if(ef == false) return true;
    return false;
}


int validate_direct_form(char *line, int labelFlag, int lineNumber){
    char input[MAX_NAME_LENGTH];
    char *token;
    int direct_type;

    strcpy(input, line);
    token = strtok(input, " ,\t\n");
    if(labelFlag){
        token = strtok(NULL, " ,\t\n");
    }

    /*now we have the command name*/
    if(token == NULL){
        printf("%d: you have to specify direct!\n", lineNumber);
        return false;
    }
    direct_type = get_direct_type(token, lineNumber);
    printf("%d\n", direct_type);
    if(direct_type == NONE){
        printf("%d: undefined command name!\n", lineNumber);
        ef = true;
    }
    else if(direct_type == STRING){
        token = strtok(NULL, " ,\t\n");
        if(token[0] != '"' || token[strlen(token)-1] != '"'){
            printf("%d: missing \"!\n", lineNumber);
            ef = true;
        }
    }
    else if(direct_type == DATA){
        token = strtok(NULL, " ,\t\n");
        while(token){
            if(!is_number(token)){
                printf("%d: argument is not a number!\n", lineNumber);
                ef = true;
            }
            token = strtok(NULL, " ,\t\n");
        }
    }
    else if(direct_type == STRUCT){
        token = strtok(NULL, " ,\t\n");
        if(!is_number(token)){
            printf("%d: argument is not a number!\n", lineNumber);
            ef = true;
        }
        token = strtok(NULL, " ,\t\n");
        if(token[0] != '"' || token[strlen(token)-1] != '"'){
            printf("%d: missing \"!\n", lineNumber);
            ef = true;
        }
        /*add more errors po*/
    }
    else if(direct_type == EXTERN){
        if(labelFlag){
            printf("%d: label can not contain external instruction\n", lineNumber);
            ef = true;
        }
        token = strtok(NULL, " ,\t\n");
        if(token == NULL){
            printf("%d: missing label argument\n", lineNumber);
            ef = true;
        }
        else if(!is_alpha_word(token)){
            printf("%d: external argument needs to be a word\n", lineNumber);
            ef = true;
        }
    }
    /*check for extra text*/

    if (ef == true) return false;
    return true;
}


int validate_instruction_form(char *line, int labelFlag, int lineNumber, int *arg1, int *arg2){
    char *token;
    char command[MAX_NAME_LENGTH];
    char input[MAX_LINE_LENGTH];
    char src_des[2][MAX_NAME_LENGTH];
    int args[2];
    int operand_num;
    int ef = 0;
    int arg;
    int i;

    strcpy(input, line);
    token = strtok(input, " ,\t\n");

    if(labelFlag){
        token = strtok(NULL, " ,\t\n");
    }
    /*now we have the command name*/
    if(token == NULL){
        printf("%d: you have to specify command!\n", lineNumber);
        return false;
    }

    if(!isOperationName(token)){
        printf("%d: undefined command name!\n", lineNumber);
        ef = true;
    }


    strcpy(command, token);
    if(ef == false){
        operand_num = getOperandNum(command);
        for(i = 0; i < operand_num; i++){
            token = strtok(NULL, " ,\t\n");
            if(token == NULL){
                printf("%d: missing argument!\n", lineNumber);
                ef = true;
                break;
            }
            puts(token);
            args[i] = get_operand_type(token);
            printf("%d\n", args[i]);

            if(args[i] == -1) printf("%d: not vaild argument!\n", lineNumber);
            if(i == 0){
                if((getSourceOperand(command) & args[i]) == 0){
                    printf("%d: not vaild argument!\n", lineNumber);
                    ef = true;
                }
            }
            if(i == 1){
                if((getDestinationOperand(command) & args[i]) == 0){
                    printf("%d: not vaild argument!\n", lineNumber);
                    ef = true;
                }
            }
            strcpy(src_des[i], token);
        }

        token = strtok(NULL, " \t\n");
        if(token != NULL){
            printf("%d: extra text after command!\n", lineNumber);
            ef = true;
        }

    }
    /*int cmdIDX;
    char *src;
    int srcType;
    char *dest;
    int destType;
    int numOfOperands;
    int lineNum;*/
    if (ef == true) return false;
    else{
        cmdArray[cmd_cnt].cmdIDX = get_cmd_IDX(command);
        strcpy(cmdArray[cmd_cnt].src, src_des[0]);/**/
        cmdArray[cmd_cnt].srcType = args[0];
        strcpy(cmdArray[cmd_cnt].dest, src_des[1]); 
        cmdArray[cmd_cnt].destType = args[1]; 
        cmdArray[cmd_cnt].numOfOperands = operand_num;
        cmdArray[cmd_cnt].lineNum = lineNumber;
        cmd_cnt++;
        *arg1 = args[0];
        *arg2 = args[1];
        return true;
    }
}

void print_cmd_line(cmdLine line){
    printf("-----------\n");
    printf(" cmdIDX = %d\n cmdSrc = %s\n cmdSrcType = %d\n cmdDest = %s\n cmdDestType = %d\n numOfOperands = %d\n lineNumber = %d\n"
            , line.cmdIDX, line.src, line.srcType, line.dest, line.destType, line.numOfOperands, line.lineNum);
    printf("-----------\n");
}

int find_L(int address1, int address2){
    int L = 0;
    if(address1 == FOURTH_ADDRESS && address2 == FOURTH_ADDRESS){
        return 1;
    }

    if(address1 == SECOND_ADDRESS) L++;
    else if(address1 == FIRST_ADDRESS) L++;
    else if(address1 == FOURTH_ADDRESS) L++;
    else if(address1 == THIRD_ADDRESS) L+=2;

    if(address2 == SECOND_ADDRESS) L++;
    else if(address2 == FIRST_ADDRESS) L++;
    else if(address2 == FOURTH_ADDRESS) L++;
    else if(address2 == THIRD_ADDRESS) L+=2;

    return L;
}


/*
first = miyadi #5
second = yashir x:
third = reshima .struct
fourth = register r1-r8
*/
int get_operand_type(char *op){
    int i = 1;
    if (op[0] == '#') return FIRST_ADDRESS;
    if(op[0] == 'r'){
        if(op[1] <= '8' && op[1] >= '1') return FOURTH_ADDRESS;
    }
    while(op[i]){
        if(op[i] == '.'){
            if(!isdigit(op[i+1])) return ERROR;
            else return THIRD_ADDRESS;
        }
        i++;
    }
    return SECOND_ADDRESS;

}

int validate_command(char *token, int lineNumber){
    return true;
}

int is_direct(char *token, int lineNumber){
    if(token == NULL) return false;
    if(token[0] == '.') return true;
    return false;
}

int get_direct_type(char *token, int lineNumber){
    int i;
    for(i=0; i < 5; i++){
        if(!strcmp(directives[i], token)) return i;
    }
    return NONE;
}


int is_label(char *token, int lineNumber){
    int len = strlen(token);
    int i;

    if(!token)
        return false;
    if(token[len-1] != ':')
        return false;

    for(i = 0; i < len-1; i++){
        if(isdigit(token[i])){
            puts("error");
            return false;
        }
    }
    return true;
}




/******utils******/


void copy_label_name(char *label, char *token){
    int size;
    strcpy(label, token);
    size = strlen(label);
    label[size-1] = LAST_CHAR;
}

int to_be_skipped(char line[]){
    int i = 0;
    i = skip_empty(line, i);
    if(line[i] == LAST_CHAR || line[i] == ';' || line[i] == '\n')
        return true;
    return false;
}

int skip_empty(char *line, int i){
    for(; i < strlen(line); i++)
    {
        if(!(line[i]==' ') || line[i]=='\t')
            return i;
    }
    return i;
}

void skip_spaces(char **p){
    int n;
    for(n = 0; ((*p)[n] == ' ' || (*p)[n] == '\t'); n++){}
    *p += n;
}

void skip_token(char **p){
    int n = 0;
    while((*p)[n] != EOF && (*p)[n] != '\n' && (*p)[n] != '\t' && (*p)[n] != ' '){
        n++;
    }
    *p +=n;
}

void skip_label(char **line){
    char input[MAX_LINE_LENGTH];
    char *token;
    strcpy(input, *line);
    token = strtok(input, " \t\n");
    if(is_label(token, 5)){
        *line += strlen(token);
    }
}

int is_alpha_word(char *word){
    int length, i;
    if(word == NULL) return false;
    length = strlen(word);

    for(i=0; i < length; i++){
        if(!isalpha(word[i])) return false;
    }
    return true;
}

int is_number(char *num){
    int length, i;
    if(num == NULL) return false;
    length = strlen(num);
    for(i=0; i < length; i++){
        if(!isdigit(num[i])) return false;
    }
    return true;
}

int get_cmd_IDX(char str[]){
    int i;
    for(i=0; i<CMD_AMOUNT; i++){
        if(!strcmp(str,ourCmd[i].name)){
            return ourCmd[i].cmdCode;
        }
    }
    return NOT_FOUND;
}

void print_cmdArray(){
    int i;
    for(i = 0; i < cmd_cnt; i++){
        print_cmd_line(cmdArray[i]);
    }
}

int check_comma(char c){
    if(c == ','){
        return 1;
    }
    return 0;
}

void skip_command(char **p){
    skip_spaces(p);
    skip_token(p);
    skip_spaces(p);
}

void get_command(char *p, char command[]){
    int j,i;
    for(i = j = 0; p[i]!= EOF && p[i] != '\n' && p[i] != ' ' && p[i] != '\t'; i++){
        command[j] = p[i];
        j++;
    }
    command[j] = LAST_CHAR;
}
