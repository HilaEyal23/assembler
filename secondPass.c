#include "secondPass.h"

extern int cmdCnt;
extern int dirCnt;
extern cmdLine cmdArray[2560];
extern dirLine dirArray[2560];
extern int ic, dc;
word cmdWordArr[2560];
word dirWordArr[2560];
extern boolean ef;
void print_word(int word);
external *extHeadGlobal;
extern boolean entryFlag;
extern boolean externFlag;

void second_pass(cmdLine cmdLines[], dirLine dirLines[], char *fileName, symbolNode *head, entry *entHead, external *extHead)
{
    
    cmdLine *cmdPtr = &cmdLines[0];
    dirLine *dirPtr = &dirLines[0];
    int i; /*goes over the given lines array one by one*/
    int idx = 0; /*the index of next empty cell in the binary-code-array*/
    extHeadGlobal = extHead;

    for(i=0; i<cmdCnt; i++){ /*encodes instruction commands*/
        idx = code_cmd_line(cmdPtr, idx, head);
        ic++;
        cmdPtr++;
    }
    ic = idx++;

    idx = 0;
    for(i=0; i<dirCnt; i++){ /*encodes data commands*/
        idx = code_dir_line(dirPtr, idx);
        dirPtr++;
    }
    dc = idx;
    if(!ef){
        create_output_files(fileName, head, entHead, extHead);
    }
}


/****** FUNCTIONS WHICH DEAL WITH ENCODING INSTRUCTION COMMANDS ******/

int code_cmd_line(cmdLine *cmdPtr, int idx, symbolNode *head){
    int offset = 1;
    cmdWordArr[idx].bits = cmdPtr->cmdIDX; /*encodes the opcode to the first word of the line*/

    switch (cmdPtr->numOfOperands) {
        case 0:
            cmdWordArr[idx].bits <<= 2 * BITS_IN_METHOD;
            cmdWordArr[idx].bits = insert_are(cmdWordArr[idx].bits, ABSOLUTE);

            return idx + offset;
        case 1:
            offset += code_cmd_operand(cmdPtr->dest, cmdPtr->destType, idx, offset, 1, head, cmdPtr->lineNum, cmdPtr->numOfOperands);

            return idx + offset;
        case 2:
            if(cmdPtr->srcType == REG_OP && cmdPtr->destType == REG_OP){
                offset += code_two_registers(idx, cmdPtr->src, cmdPtr->dest, offset);

                return idx + offset;
            }
            offset += code_cmd_operand(cmdPtr->src, cmdPtr->srcType, idx, offset, 1, head, cmdPtr->lineNum, cmdPtr->numOfOperands);
            offset += code_cmd_operand(cmdPtr->dest, cmdPtr->destType, idx, offset, 2, head, cmdPtr->lineNum, cmdPtr->numOfOperands);

            return idx + offset;
        default:
            return 0;
    }
}


int code_cmd_operand(char *operand, int type, int idx, int currOffset, int operandNum, symbolNode *head, int lineNum, int numOfOperands){
    switch (type) {
        case IMMEDIATE_OP:
            return code_immediate(idx, operand, operandNum, currOffset, numOfOperands);
        case DIRECT_OP:
            return code_direct(idx, operand, operandNum, head, currOffset, lineNum, numOfOperands);
        case STRUCT_OP:
            return code_relative(idx, operand, operandNum, head, currOffset, lineNum, numOfOperands);
        case REG_OP:
            return code_register(idx, operand, operandNum, currOffset, numOfOperands);
        default:
            return 0;
    }
}


int code_immediate(int idx, char *operand, int operandNum, int currOffset, int numOfOperands){
    char positive[MAX_LINE_LENGTH] = {0};

    if(operandNum == 1){
        if(numOfOperands == 1) {
            cmdWordArr[idx].bits <<= 2 * BITS_IN_METHOD;
            cmdWordArr[idx].bits |= IMMEDIATE;
            cmdWordArr[idx].bits = insert_are(cmdWordArr[idx].bits, ABSOLUTE);
        }
        else{
            cmdWordArr[idx].bits <<= BITS_IN_METHOD;
            cmdWordArr[idx].bits |= IMMEDIATE;
        }
    }
    else{
        cmdWordArr[idx].bits <<= BITS_IN_METHOD;
        cmdWordArr[idx].bits |= IMMEDIATE;
        cmdWordArr[idx].bits = insert_are(cmdWordArr[idx].bits, ABSOLUTE);
    }

    operand++; /*skips '#'*/

    if(operand[0] == '-'){
        strcpy(positive, &operand[1]);
        cmdWordArr[idx + currOffset].bits = -1 * atoi(positive);

    }
    else {
        cmdWordArr[idx + currOffset].bits = atoi(operand);

    }

    cmdWordArr[idx + currOffset].bits = insert_are(cmdWordArr[idx + currOffset].bits, ABSOLUTE);
    return 1;
}



int code_direct(int idx, char *operand, int operandNum, symbolNode *head, int currOffset, int lineNum, int numOfOperands){
    unsigned int address = find_symbol_address(head, operand);

    if(address == NOT_FOUND){
        puts("hi");
        address = find_extern_address(extHeadGlobal, operand);
        if(address == NOT_FOUND){
        ef = true;
        printf("error in line %d: %s is not found\n", lineNum, operand);
        return 0;
        }
    }
    
    if(operandNum == 1){
        if(numOfOperands == 1) {
            cmdWordArr[idx].bits <<= 2 * BITS_IN_METHOD;
            cmdWordArr[idx].bits |= DIRECT;
            cmdWordArr[idx].bits = insert_are(cmdWordArr[idx].bits, ABSOLUTE);
        }
        else{
            cmdWordArr[idx].bits <<= BITS_IN_METHOD;
            cmdWordArr[idx].bits |= DIRECT;
        }
    }
    else{
        cmdWordArr[idx].bits <<= BITS_IN_METHOD;
        cmdWordArr[idx].bits |= DIRECT;
        cmdWordArr[idx].bits = insert_are(cmdWordArr[idx].bits, ABSOLUTE);
    }

    cmdWordArr[currOffset + idx].bits = address;
    if(find_symbol_type(head, operand) == EXTERNAL){
        extern_exists = true;
        /*code_extern_dir(idx);*/
        cmdWordArr[currOffset + idx].bits = insert_are(cmdWordArr[currOffset + idx].bits, EXTERNAL);
        return 1;
    }
    cmdWordArr[idx + currOffset].bits = insert_are(cmdWordArr[currOffset + idx].bits, RELOCATABLE);
    return 1;
}

int code_relative(int idx, char *operand, int operandNum, symbolNode *head, int currOffset, int lineNum, int numOfOperands) {
    unsigned int address;
    char *token;
    char operandCopy[MAX_LINE_LENGTH];

    strcpy(operandCopy, operand);
    token = strtok(operandCopy, "."); /*struct-name.field-number*/
    address = find_symbol_address(head, token);
    if(address == NOT_FOUND){
        address = find_extern_address(extHeadGlobal, operand);
        if(address == NOT_FOUND){
            ef = true;
            printf("error in line %d: %s is not found\n", lineNum, token);
            return 0;
        }   
    }
    

    if(operandNum == 1){
        if(numOfOperands == 1) {
            cmdWordArr[idx].bits <<= 2 * BITS_IN_METHOD;
            cmdWordArr[idx].bits |= RELATIVE;
            cmdWordArr[idx].bits = insert_are(cmdWordArr[idx].bits, ABSOLUTE);
        }
        else{
            cmdWordArr[idx].bits <<= BITS_IN_METHOD;
            cmdWordArr[idx].bits |= RELATIVE;
        }
    }
    else{
        cmdWordArr[idx].bits <<= BITS_IN_METHOD;
        cmdWordArr[idx].bits |= RELATIVE;
        cmdWordArr[idx].bits = insert_are(cmdWordArr[idx].bits, ABSOLUTE);
    }

    token = strtok(NULL, " \n");
    cmdWordArr[currOffset + idx].bits = atoi(token);
    if(find_symbol_type(head, operand) == EXTERNAL){
        extern_exists = true;
        /*code_extern_dir(idx);*/
        cmdWordArr[currOffset + idx].bits = insert_are(cmdWordArr[currOffset + idx].bits, EXTERNAL);
        return 2;
    }
    cmdWordArr[idx + currOffset].bits = insert_are(cmdWordArr[currOffset + idx].bits, RELOCATABLE);
    return 2;
}

int code_register(int idx, char *operand, int operandNum, int currOffset, int numOfOperands){
    unsigned int registerIdx;

    if(operandNum == 1){
        if(numOfOperands == 1) {
            cmdWordArr[idx].bits <<= 2 * BITS_IN_METHOD;
            cmdWordArr[idx].bits |= REGISTER;
            cmdWordArr[idx].bits = insert_are(cmdWordArr[idx].bits, ABSOLUTE);
        }
        else{
            cmdWordArr[idx].bits <<= BITS_IN_METHOD;
            cmdWordArr[idx].bits |= REGISTER;
        }
    }
    else{
        cmdWordArr[idx].bits <<= BITS_IN_METHOD;
        cmdWordArr[idx].bits |= REGISTER;
        cmdWordArr[idx].bits = insert_are(cmdWordArr[idx].bits, ABSOLUTE);
    }

    registerIdx = operand[1] - '0'; /* convert argument[1] to int */
    if(operandNum == 1){
        cmdWordArr[idx + currOffset].bits = registerIdx;
        cmdWordArr[idx + currOffset].bits <<= BITS_IN_REGISTER;
        cmdWordArr[idx + currOffset].bits = insert_are(cmdWordArr[idx + currOffset].bits, ABSOLUTE);
        return 1;
    }
    cmdWordArr[idx + currOffset].bits <<= 2 * BITS_IN_REGISTER;
    cmdWordArr[idx + currOffset].bits |= registerIdx;
    cmdWordArr[idx + currOffset].bits = insert_are(cmdWordArr[idx + currOffset].bits, ABSOLUTE);
    return 1;

}

int code_two_registers(int idx, char *src, char *dest, int currOffset)
{
    unsigned int registerIdx;
    cmdWordArr[idx].bits <<= BITS_IN_METHOD;
    cmdWordArr[idx].bits |= REGISTER;
    cmdWordArr[idx].bits <<= BITS_IN_METHOD;
    cmdWordArr[idx].bits |= REGISTER;
    cmdWordArr[idx].bits = insert_are(cmdWordArr[idx].bits, ABSOLUTE);

    registerIdx = src[1] - '0'; /* convert argument[1] to int */
    cmdWordArr[idx + currOffset].bits = registerIdx;
    cmdWordArr[idx + currOffset].bits <<= BITS_IN_REGISTER;
    registerIdx = dest[1] - '0'; /* convert argument[1] to int */
    cmdWordArr[idx + currOffset].bits |= registerIdx;
    cmdWordArr[idx + currOffset].bits = insert_are(cmdWordArr[idx + currOffset].bits, ABSOLUTE);

    return 1;
}



/****** FUNCTIONS WHICH DEAL WITH ENCODING DIRECTIVE COMMANDS ******/

int code_dir_line(dirLine *dirPtr, int idx){
    switch(dirPtr->dirType){
        case DATA:
            return code_data_dir(dirPtr->operands, dirPtr->operand_cnt, idx);
        case STRING:
            return code_string_dir(dirPtr->operands, idx, 0);
        case STRUCT:
            return code_struct_dir(dirPtr->operands, idx);
        default:
            return 0;
    }
}

int code_data_dir(char operand[][MAX_NAME_LENGTH], int numOfOperands, int idx){
    int currOffset;
    for(currOffset=0; currOffset < numOfOperands ; currOffset++){
        dirWordArr[idx + currOffset].bits = atoi(operand[currOffset]);
    }
    return idx + currOffset;
}


int code_string_dir(char operand[][MAX_NAME_LENGTH], int idx, int structIdx){
    int currOffset = 0;

    while(operand[structIdx][currOffset] != '\0' && operand[structIdx][currOffset] != '"') {
        dirWordArr[idx + currOffset].bits = operand[structIdx][currOffset] - '\0'; /* convert argument[1] to int */
        currOffset++;
    }
    dirWordArr[idx + currOffset].bits = 0;
    currOffset++;

    return idx + currOffset;
}

int code_struct_dir(char operand[][MAX_NAME_LENGTH], int idx){
    int currOffset = 0;

    dirWordArr[idx].bits = atoi(operand[0]);
    currOffset++;

    while(operand[1][currOffset] != '\0' && operand[1][currOffset] != '"') {
        dirWordArr[idx + currOffset].bits = operand[1][currOffset] - '\0'; /* convert argument[1] to int */

        currOffset++;
    }
    dirWordArr[idx + currOffset].bits = 0;
    currOffset++;
    
    return idx + currOffset;
}


/****** FUNCTIONS WHICH DEAL WITH OUTPUT FILES ******/

int create_output_files(char *fileName, symbolNode *head, entry *entHead, external *extHead){
    FILE *file;
    file = open_file(fileName, FILE_OBJECT);
    create_ob_file(file);

    if(entryFlag) {
        file = open_file(fileName, FILE_ENTRY);
        create_entry_file(file, head, entHead);
    }
    if(externFlag){
        file = open_file(fileName, FILE_EXTERN);
        create_extern_file(file, extHead);
    }

    return NO_ERROR;
}



void create_ob_file(FILE *fp)

{
    unsigned int address = IC_INIT_VALUE;
    int idx;
    char *param1 = convert_to_base_32(ic), *param2 = convert_to_base_32(dc);

    fprintf(fp, "\t\t\t\t\t\t\t\t%s\t\t\t\t%s\n\n", param1, param2); /* First line */
    free(param1);
    free(param2);



    for (idx = 0; idx < ic; address++, idx++) /* Instructions memory */
    {

        param1 = convert_to_base_32(address);
        param2 = convert_to_base_32(cmdWordArr[idx].bits);

        fprintf(fp, "\t\t\t\t\t\t\t\t%s\t\t\t\t%s\n\n", param1, param2);
        free(param1);
        free(param2);
    }


    for (idx = 0; idx < dc; address++, idx++) /* Instructions memory */
    {

        param1 = convert_to_base_32(address);
        param2 = convert_to_base_32(dirWordArr[idx].bits);

        fprintf(fp, "\t\t\t\t\t\t\t\t%s\t\t\t\t%s\n\n", param1, param2);
        free(param1);
        free(param2);
    }
    fclose(fp);
}


void create_entry_file(FILE *fp, symbolNode *head, entry *entHead)
{
    char *base32_address;
    symbolNode *label = head;
   
    
    while(entHead){
         while(label)
        {
        if(!strcmp(label->currentNode.name, entHead->name)){
            /*printf("typeee: %d",label->currentNode.type);*/
            base32_address = convert_to_base_32(label->currentNode.address);
            fprintf(fp, "%s\t%s\n", label->currentNode.name, base32_address);
            free(base32_address);
        }
        label = label -> next;
        }
        label = head;
        entHead = entHead->next;
    }
    fclose(fp);
}
void create_extern_file(FILE *fp, external *extHead)
{   int i;
    char *base32_address;
    while(extHead){
        for(i = 0; i < cmdCnt; i++){
            if(!strcmp(cmdArray[i].src, extHead->name) || !strcmp(cmdArray[i].dest, extHead->name)){
                base32_address = convert_to_base_32(cmdArray[i].IC);
                fprintf(fp, "%s\t%s\n", extHead->name, base32_address);
            }
        }
        extHead = extHead -> next;
    }
    fclose(fp);
}


FILE *open_file(char *filename, int type)
{
    FILE *file;
    filename = create_file_name(filename, type); /* Creating filename with extension */

    file = fopen(filename, "w"); /* Opening file with permissions */
    free(filename); /* Allocated modified filename is no longer needed */

    if(file == NULL)
    {
        printf("error while creating a file\n");
        ef = true;
        return NULL;
    }
    return file;

}


/****** FUNCTIONS WHICH DEAL WITH DEBUGGING ******/


void print_binary(unsigned int number)
{
    if (number >> 1) {
        print_binary(number >> 1);
    }
    putc((number & 1) ? '1' : '0', stdout);
}

void print_line_binary(int idx, int offset)
{
    int i;
    for(i=idx; i<idx+offset; i++){
        printf("the %d word:", i);
        print_binary(cmdWordArr[i].bits);
        printf("\n");
    }
}
