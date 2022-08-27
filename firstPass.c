#include "firstPass.h"

char directives[5][8] = {".data", ".string", ".struct", ".entry", ".extern"};
extern boolean ef;
cmdLine cmdArray[40];
dirLine dirArray[40];
extern int dirCnt;
extern int cmdCnt;
boolean entryFlag = 0;
boolean externFlag = 0;


/******MAIN FUNTIONS IN FIRST PASS******/

void first_pass(FILE *fp, char *fileName, symbolNode **head, entry **entHead, external **extHead){
    int lineNumber = 1;
    char line[MAX_LINE_LENGTH];
    char linesCopy[MAX_LINE_LENGTH];
    char label[MAX_NAME_LENGTH];
    char *token;
    int labelFlag = false;
    int directFlag = false;
    int directType;
    int args[2];
    int IC = IC_INIT_VALUE;
    int DC = DC_INIT_VALUE;
    int DCL = 0;

    *head = init_symbol_node(NULL, "999", 0, -1);
    *entHead = init_entry_node(NULL, "999");
    *extHead = init_extern_node(NULL, "999");
    while(fgets(line, MAX_LINE_LENGTH, fp)){
        strcpy(linesCopy, line);
        if(!to_be_skipped(line)){
            token = strtok(line, " \t\n");
            if(is_label(token, lineNumber)){
                
                copy_label_name(label, token);
                if(symbol_exists(*head ,label)){
                    printf("label is already defined!\n");
                }
                
                labelFlag = true;
                
		        token = strtok(NULL, " \t\n");
            }
            /*validate_input_form(line, lineNumber, labelFlag);*/
            if(is_direct(token, lineNumber)){
                directFlag = true;
                if(validate_direct_form(linesCopy, labelFlag, lineNumber, &DCL, *entHead, *extHead)){/*create this function*/
                    directType = get_direct_type(token, lineNumber);
                }
            }
            if(directFlag && labelFlag && ef == 0){
                insert_symbol(*head, label, DC, directType);
                DC+=DCL;
            }/*if it is not direct then it is code*/
            else if(!directFlag && validate_instruction_form(linesCopy, labelFlag, lineNumber, &args[0], &args[1], IC)){
                if(labelFlag &&  ef == 0){
                    insert_symbol(*head, label, IC, CODE);
                    IC += find_L(args[0], args[1])+1;
                }
            }
        }
        labelFlag = false;
        directFlag = false;
        lineNumber++;
        DCL = 0;
    }
    add_IC_to_directs(*head, IC); /*the data become after the commands so we add each data the IC counter*/
}

void add_IC_to_directs(symbolNode *head, int IC){
    while(head){
        if(head->currentNode.type < 5) head->currentNode.address += IC;
        head = head->next;
    }
}


int find_L(int address1, int address2){
    int L = 0;
    if(address1 == REG_OP && address2 == REG_OP){
        return 1;
    }

    if(address1 == DIRECT_OP) L++;
    else if(address1 == IMMEDIATE_OP) L++;
    else if(address1 == REG_OP) L++;
    else if(address1 == STRUCT_OP) L+=2;

    if(address2 == DIRECT_OP) L++;
    else if(address2 == IMMEDIATE_OP) L++;
    else if(address2 == REG_OP) L++;
    else if(address2 == STRUCT_OP) L+=2;

    return L;
}


int get_operand_type(char *op){
    int i = 0;
    if (op[0] == '#'){
        if(is_number(op+1)){
            return IMMEDIATE_OP;
        }
    }
    else if(op[0] == 'r'){
        if(op[1] <= '8' && op[1] >= '1'&&!op[2]) return REG_OP;
    }
    while(op[i+1]){
        if(op[i] == '.'){
            if(isdigit(op[i+1])){
                return STRUCT_OP;
            }
        }
        i++;
    }

    if(validate_label(op)) return DIRECT_OP;
    
    return -1;

}

int validate_label(char *token){
    int i;
  if (!isalpha(token[0])){
        printf("illegal label name!\n");
        return false;
    }
        
    for (i = 1; i < strlen(token) - 1; i++) /*after that we check if it is a unvaild symbol line * */
    {
        if (!isalpha(token[i]) && !isdigit(token[i]))
            return true;
    }

    /* Loop over each command, and check if it's name is equal to a known command */
    

    /* check for directives*/
    for(i = 0; i < 5; i++){
        if(!strcmp(directives[i], token)){
            printf("label can't be a directive!\n");
            return false;
        }
    }

    return true;

}


int get_direct_type(char *token, int lineNumber){
    int i;
    for(i=0; i < 5; i++){
        if(!strcmp(directives[i], token)) return i;
    }
    return NONE;
}

void get_command(char *p, char command[]){
    int j,i;
    for(i = j = 0; p[i]!= EOF && p[i] != '\n' && p[i] != ' ' && p[i] != '\t'; i++){
        command[j] = p[i];
        j++;
    }
    command[j] = LAST_CHAR;
}



/******VALIDATION FUNCTIONS******/

int validate_command(char *token, int lineNumber){
    return true;
}
void validate_input_form(char input[], int labelFlag, int lineNumber){
    int comma_cnt = 0;
    int tokens_cnt = 0;
    char *line = input;
    if(labelFlag){
        skip_command(&line);
    }
    skip_spaces(&line);
    skip_command(&line);
    if(check_comma(line[0])){
        printf("%d: illegal comma!\n", lineNumber);
        ef = 1;
    }
    while(line[0] != '\n' && line[0] != EOF){
        skip_command(&line);
        tokens_cnt++;
        if(!check_comma(line[0])){
            skip_spaces(&line);
            if(line[0] == '\n' || line[0] == EOF || !line[0]){
                break;
            }
            else{
                printf("%d: missing comma!\n", lineNumber);
                ef = 1;
            }
        }
        else{
            comma_cnt++;
            line++;
        }
        skip_spaces(&line);
        if(check_comma(line[0])){
            printf("%d:double comma!\n", lineNumber);
            ef = 1;
        }
    }



}



int validate_direct_form(char *line, int labelFlag, int lineNumber, int *DCL, entry *entHead, external *extHead){
    char input[MAX_NAME_LENGTH];
    char *token;
    int direct_type;
    strcpy(input, line);
    validate_input_form(input, labelFlag, lineNumber);
    token = strtok(input, " ,\t\n");
    if(labelFlag){ /*if it is fkag so we need to get one more token to reach arguments*/
        token = strtok(NULL, " ,\t\n");
    }
    /*now we have the command name*/
    if(token == NULL){
        printf("%d: you have to specify direct!\n", lineNumber);
        return false;
    }
    direct_type = get_direct_type(token, lineNumber); /*we get the direct type here*/
    if(direct_type == NONE){
        printf("%d: undefined command name!\n", lineNumber);
        ef = true;
    }
    else if(direct_type == STRING){
		validate_string(&DCL, lineNumber, labelFlag);
    }
    else if(direct_type == DATA){
		validate_data(&DCL, lineNumber, labelFlag);
    }
    else if(direct_type == STRUCT){
        validate_struct(&DCL, lineNumber, labelFlag);
    }
    else if(direct_type == EXTERN){
        validate_extern(&DCL, lineNumber, labelFlag, extHead);
    }
  
    else if(direct_type == ENTRY){
        validate_entry(&DCL, lineNumber, labelFlag, entHead);
    }
	token = strtok(NULL, " ,\t\n");
    check_extra_text(token, lineNumber);
    if (ef == true) return false;
    else{
      	dirArray[dirCnt].dirType = direct_type;
		dirArray[dirCnt].lineNum = lineNumber;
		dirCnt++;
        return true;
    }
}

int check_extra_text(char *token, int lineNumber){
    if(token != NULL){
        printf("%d: extra text after command!\n", lineNumber);
        ef = true;
        return false;
    }
    return true;
}

void validate_data(int **DCL, int lineNumber, int labelFlag){
    int D = 0;
    char *token;
    dirArray[dirCnt].operand_cnt = 0;

    token = strtok(NULL, " ,\t\n"); /*we take the first argument*/
    
    while(token){
        D++; /*we have just found another argument so we update L*/
        if(!is_number(token)){
            printf("%d: argument is not a number!\n", lineNumber);
            ef = true;
        }
        /*we add the data to the direct array so we can code it*/
		strcpy(dirArray[dirCnt].operands[dirArray[dirCnt].operand_cnt], token);
		dirArray[dirCnt].operand_cnt++;
        /*we are taking the next token*/
        if(token != NULL){
            token = strtok(NULL, " ,\t\n");
        }
			
    }
    **DCL = D;
}

void validate_string(int **DCL, int lineNumber, int labelFlag){
    int D = 0;

    char *token;
    dirArray[dirCnt].operand_cnt = 0;
        token = strtok(NULL, " ,\t\n");
        if(!token){
            printf("%d: missing argument!\n", lineNumber);
            ef = true;
            return;
        }
        if(token[0] != '"' || token[strlen(token)-1] != '"'){
            printf("%d: missing \"!\n", lineNumber);
            ef = true;
        }
        token = strtok(token, "\"");
        if(!is_alpha_word(token)){ /*if the argument is null we print error because the argument is missing*/
            printf("%d: argument is not a string!\n", lineNumber);
            ef = true;
            return;
        }
        D = strlen(token)-1;
		if(ef == 0){
			strcpy(dirArray[dirCnt].operands[dirArray[dirCnt].operand_cnt], token);
			dirArray[dirCnt].operand_cnt++;
		}
        **DCL = D;
}

void validate_entry(int **DCL, int lineNumber, int labelFlag, entry *entHead){
    char *token;
    int D = 0;
    if(labelFlag){
        printf("%d: label can not contain entry instruction\n", lineNumber);
        ef = true;
    }
    token = strtok(NULL, " ,\t\n");        
    if(token == NULL){
        printf("%d: missing label argument\n", lineNumber);
        ef = true;
        return;
    }
    else if(!is_alpha_word(token)){
        printf("%d: entry's argument needs to be a label name!\n", lineNumber);
        ef = true;
    }
	strcpy(dirArray[dirCnt].operands[dirArray[dirCnt].operand_cnt], token);
	dirArray[dirCnt].operand_cnt++;
    insert_entry(entHead, token);
    entryFlag = 1;
    **DCL = D;
    
}

void validate_extern(int **DCL, int lineNumber, int labelFlag, external *extHead){
    char *token;
    int D = 0;
    if(labelFlag){ /*extern can not become after label defeniftion*/
        printf("%d: label can not contain external instruction\n", lineNumber);
        ef = true;
    }
    token = strtok(NULL, " ,\t\n");
    if(token == NULL){
        printf("%d: missing label argument\n", lineNumber);
        ef = true;   
        return;
    }
    else if(!validate_label(token)){
        printf("%d: external's argument needs to be a label name!\n", lineNumber);
        ef = true;
    }
	strcpy(dirArray[dirCnt].operands[dirArray[dirCnt].operand_cnt], token);
	dirArray[dirCnt].operand_cnt++;
    insert_extern(extHead, token);
    externFlag = 1;
    **DCL = D;
}


void validate_struct(int **DCL, int lineNumber, int labelFlag){
    char *token;
    int D = 0;
    token = strtok(NULL, " ,\t\n"); /*we take the first argument*/
    if(token == NULL){
        printf("%d: missing number argument\n", lineNumber);
        ef = true;   
        return;
    }
    if(!is_number(token)){ /*if the argument is null we print error because the argument is missing*/
        printf("%d: argument is not a number!\n", lineNumber);
        ef = true;
    }
    /*We now have to add 1 for the ID's L*/
    D++;
	strcpy(dirArray[dirCnt].operands[dirArray[dirCnt].operand_cnt], token);
	dirArray[dirCnt].operand_cnt++;
    token = strtok(NULL, " ,\t\n"); /*we now take the second argument*/
    if(!token){ /*if the argument is null we print error because the argument is missing*/
        printf("%d: missing argument!\n", lineNumber);
        ef = true;
        return;
    }
    if(token[0] != '"' || token[strlen(token)-1] != '"'){
        printf("%d: missing \"!\n", lineNumber);
        ef = true;
    }
    D+= strlen(token)-1;
	strcpy(dirArray[dirCnt].operands[dirArray[dirCnt].operand_cnt], token);
	dirArray[dirCnt].operand_cnt++;
    /*add more errors po*/
    **DCL = D;
}





int validate_instruction_form(char *line, int labelFlag, int lineNumber, int *arg1, int *arg2, int IC){
    char *token;
    char command[MAX_NAME_LENGTH];
    char input[MAX_LINE_LENGTH];
    char src_des[2][MAX_NAME_LENGTH];
    int args[2];
    int operand_num;
    int ef = 0;
    int i;

    strcpy(input, line);
    token = strtok(input, " ,\t\n");

    if(labelFlag){
        token = strtok(NULL, " ,\t\n");
    }
    /*now we have the command name*/
    if(token == NULL){
        printf("%d: you have to specify command!\n", lineNumber);
        ef = 1;
        return false;
    }

    if(!is_operation(token)){
        printf("%d: undefined command name!\n", lineNumber);
        ef = true;
    }


    strcpy(command, token);
    if(ef == false){
        operand_num = get_operand_num(command);
        
    

        if(operand_num == 1){
            token = strtok(NULL, " ,\t\n");
            if(token == NULL){
                printf("%d: missing argument!\n", lineNumber);
                ef = true;
            }
            args[1] = get_operand_type(token);
            if(args[1] == -1) printf("%d: not vaild argument!\n", lineNumber);
            if((get_dest_operand(command) & args[1]) == 0){
                printf("%d: not vaild argument!\n", lineNumber);
                ef = true;
            }
            strcpy(src_des[1], token);
        }
        else if(operand_num == 2){
            for(i = 0; i < operand_num; i++){
            token = strtok(NULL, " ,\t\n");
            if(token == NULL){
                printf("%d: missing argument!\n", lineNumber);
                ef = true;
                break;
            }
            args[i] = get_operand_type(token);
            if(args[i] == -1) printf("%d: not vaild argument!\n", lineNumber);
            if(i == 0){
                if((get_src_operand(command) & args[i]) == 0){
                    printf("%d\n", get_src_operand(command));
                    printf("%d: not vaild argument!\n", lineNumber);
                    ef = true;
                }
            }
            if(i == 1){
                if((get_dest_operand(command) & args[i]) == 0){
                    printf("%d: not vaild argument!\n", lineNumber);
                    ef = true;
                }
            }
            strcpy(src_des[i], token);
        }
        }
    

        token = strtok(NULL, " \t\n");
        if(token != NULL){
            printf("%d: extra text after command!\n", lineNumber);
            ef = true;
        }

    }
    if (ef == true) return false;
    else{
        cmdArray[cmdCnt].IC = IC;
        cmdArray[cmdCnt].cmdIDX = get_operation_opcode(command);
        strcpy(cmdArray[cmdCnt].src, src_des[0]);/**/
        cmdArray[cmdCnt].srcType = args[0];
        strcpy(cmdArray[cmdCnt].dest, src_des[1]); 
        cmdArray[cmdCnt].destType = args[1]; 
        cmdArray[cmdCnt].numOfOperands = operand_num;
        cmdArray[cmdCnt].lineNum = lineNumber;
        cmdCnt++;
        *arg1 = args[0];
        *arg2 = args[1];
        return true;
    }
}



/******PARSING FUNCTIONS******/

void skip_command(char **p){
    skip_spaces(p);
    skip_token(p);
    skip_spaces(p);
}

int check_comma(char c){
    if(c == ','){
        return 1;
    }
    return 0;
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
    while((*p)[n] != EOF && (*p)[n] != '\n' && (*p)[n] != '\t' && (*p)[n] != ' ' && (*p)[n] != ','){
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

int to_be_skipped(char line[]){
    int i = 0;
    i = skip_empty(line, i);
    if(line[i] == LAST_CHAR || line[i] == ';' || line[i] == '\n')
        return true;
    return false;
}

void copy_label_name(char *label, char *token){
    int size;
    strcpy(label, token);
    size = strlen(label);
    label[size-1] = LAST_CHAR;
}

boolean end_of_line(char *line){
    return line == NULL || *line == '\0' || *line =='\n';
}



/******DETECTING FUNCTIONS******/

int is_label(char *token, int lineNumber){

    int i;

    
    if(token[strlen(token)-1] != ':') return false;
    /*firstly we have to check if the first letter is a digit, this is unvaild*/
    if (!isalpha(token[0])){
        printf("%d: illegal label name!\n", lineNumber);
        return true;
    }
        
    for (i = 1; i < strlen(token) - 1; i++) /*after that we check if it is a unvaild symbol line * */
    {
        if (!isalpha(token[i]) && !isdigit(token[i]))
            return true;
    }

    /* Loop over each command, and check if it's name is equal to a known command */
    

    /* check for directives*/
    for(i = 0; i < 5; i++){
        if(!strcmp(directives[i], token)){
            printf("%d: label can't be a directive!\n", lineNumber);
        }
    }

    return true;
}

int is_direct(char *token, int lineNumber){
    if(token == NULL) return false;
    if(token[0] == '.') return true;
    return false;
}


int is_number(char *seq){
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


int is_alpha_word(char *word){
    int length, i;
    if(word == NULL) return false;
    length = strlen(word);

    for(i=0; i < length; i++){
        if(!isalpha(word[i])) return false;
    }
    return true;
}



/******DEBUG TOOLS******/

void print_cmdArray(){
    int i;
    for(i = 0; i < cmdCnt; i++){
        print_cmd_line(cmdArray[i]);
    }
}

void print_cmd_line(cmdLine line){
    printf("-----------\n");
    printf(" cmdIDX = %d\n cmdSrc = %s\n cmdSrcType = %d\n cmdDest = %s\n cmdDestType = %d\n numOfOperands = %d\n lineNumber = %d\n"
            , line.cmdIDX, line.src, line.srcType, line.dest, line.destType, line.numOfOperands, line.lineNum);
    printf("-----------\n");
}

void print_dirArray(){
	int i;
	for(i = 0; i < dirCnt; i++){
		print_dir_line(dirArray[i]);
	}
}

void print_dir_line(dirLine line){
	int i;
    printf("-----------\n");
    printf("type = %d\n line = %d\n",
            line.dirType, line.lineNum);
	for(i = 0; i < line.operand_cnt; i++){
		printf("opernad %d = %s\n", i, line.operands[i]);
	}
    printf("-----------\n");
}
