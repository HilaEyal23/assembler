#include "globals.h"
#include "utils.h"
/*#include "symbolList.h"*/
#include "externVars.h"

extern int cmdCnt;
extern int ic, dc;
word cmdWordArr[2560];

void second_pass(cmdLine cmdLines[], char *fileName);
int code_cmd_line(cmdLine *cmdPtr, int idx);
int code_cmd_operand(char *operand, int type, int idx, int currOffset, int operandNum, int lineNum);
int code_immediate(int idx, char *operand, int operandNum, int currOffset);
/*int code_direct(int idx, char *operand, int operandNum, symbolNode *head, int *flag, int *EXT_VAR, int currOffset);
int code_relative(int idx, char *operand, int operandNum, symbolNode *head, int *EXT_VAR, int *flag, int currOffset, int lineNum);*/
int code_two_registers(int idx, char *src, char *dest, int currOffset);
int code_register(int idx, char *operand, int operandNum, int currOffset);

int create_output_files(char *filename);
void create_ob_file(FILE *file);
void create_entry_file(FILE *file);
void create_extern_file(FILE *file);
FILE *open_file(char *filename, int type);


void second_pass(cmdLine cmdLines[], char *fileName)
{
    cmdLine *cmdPtr = &cmdLines[0];
    int i;
    int idx = 0;
    const char base32[32] = {
            '!', '@', '#', '$', '%', '^', '&', '*',
            '<','>', 'a', 'b', 'c','d', 'e', 'f',
            'g','h', 'i', 'j', 'k', 'l', 'm', 'n',
            'o', 'p','q', 'r', 's', 't', 'u', 'v'
    };


    for(i=0; i<cmdCnt; i++){ /*encodes instruction commands*/
        printf("\nopcode: %d\n", cmdPtr->cmdIDX);
        printf("numOfOperands: %d\n", cmdPtr->numOfOperands);
        code_cmd_line(cmdPtr, idx);
        ic++;
        /*idx++;*/
        cmdPtr++;
    }

    create_output_files("test");
}



int code_cmd_line(cmdLine *cmdPtr, int idx){
    int offset = 1;
    cmdWordArr[idx].bits = 0;
    cmdWordArr[idx].bits += cmdPtr->cmdIDX; /*encodes the opcode to the first word of the line*/
    cmdWordArr[idx].bits = cmdWordArr->bits << BITS_IN_OPCODE;

    switch (cmdPtr->numOfOperands) {
        case 0:
            return idx + offset;
        case 1:
            offset += code_cmd_operand(cmdPtr->dest, cmdPtr->destType, idx, offset, 1, cmdPtr->lineNum);
            return idx + offset;
        case 2:
            if(cmdPtr->srcType == FOURTH_ADDRESS && cmdPtr->destType == FOURTH_ADDRESS){
                offset += code_two_registers(idx, cmdPtr->src, cmdPtr->dest, offset);
                return idx + offset;
            }
            offset += code_cmd_operand(cmdPtr->src, cmdPtr->srcType, idx, offset, 1, cmdPtr->lineNum);
            offset += code_cmd_operand(cmdPtr->dest, cmdPtr->destType, idx, offset, 2, cmdPtr->lineNum);
            return idx + offset;
        default:
            printf("default case code_cmd_line()\n");
            printf("%d\n",cmdPtr->numOfOperands);
            return 0;
    }
}


int code_cmd_operand(char *operand, int type, int idx, int currOffset, int operandNum, int lineNum){
    printf("type: %d\n", type);
    switch (type) {
        case FIRST_ADDRESS:
            return code_immediate(idx, operand, operandNum, currOffset);
            /* case SECOND_ADDRESS:
                 return code_direct(idx, operand, operandNum, currOffset);
             case THIRD_ADDRESS:
                 return code_relative(idx, operand, operandNum, currOffset, lineNum);*/
        case FOURTH_ADDRESS:
            return code_register(idx, operand, operandNum, currOffset);
        default:
            printf("default case code_cmd_operand()\n");
            return 0;
    }
}


int code_immediate(int idx, char *operand, int operandNum, int currOffset){
    char positive[MAX_LINE_LENGTH] = {0};
    cmdWordArr[idx].bits += IMMEDIATE;
    cmdWordArr[idx].bits << BITS_IN_METHOD;
    if(operandNum == 2)
        cmdWordArr[idx].bits = insert_are(cmdWordArr[idx].bits, ABSOLUTE);

    if(operand[0] == '-'){
        strcpy(positive, &operand[1]);
        cmdWordArr[idx + currOffset].bits += -1 * atoi(positive);
        printf("operand: %d\n", -1*atoi(positive));
    }
    else {
        cmdWordArr[idx + currOffset].bits = atoi(operand);
        printf("operand: %d\n", atoi(operand));
    }

    cmdWordArr[idx + currOffset].bits = insert_are(cmdWordArr[idx].bits, ABSOLUTE);
    return 1;
}



/*
int code_direct(int idx, char *operand, int operandNum, symbolNode *head, int currOffset, int lineNum){
    symbolNode *ptr = head;
    while(ptr){
        if(!strcmp(ptr->currSymbol.name, operand)){
            cmdWordArr[idx].bits += DIRECT;
            cmdWordArr[idx].bits << BITS_IN_METHOD;
            cmdWordArr[currOffset + idx].bits = ptr->currSymbol.value;
            if(ptr->currSymbol.type == EXTERNAL){
                extern_exists = true;
                code_extern_dir(idx);
                return 1;
            }
            insert_are(cmdWordArr[currOffset + idx].bits, RELOCATABLE);
            return 1;
        }
    }
    err = true;
    printf("error in line %d: label is not found\n", lineNum);

    return 0;
}*/
/*to be fixed*/ /*
int code_relative(int idx, char *operand, int operandNum, symbolNode *head, int currOffset, int lineNum){
    cmdWordArr[idx].bits += RELATIVE;
    cmdWordArr[idx].bits << BITS_IN_METHOD;
    char *token;
    char operandCopy[MAX_LINE_LENGTH];
    int value;

    strcpy(operandCopy, operand);
    token = strtok(operandCopy, ".");
    value = find_symbol_value(head, token);
    if (value == NOT_FOUND){
        err = true;
        printf("error: line %d,struct does not exists\n", lineNum);
        return 2;
    }
    cmdWordArr[currOffset + idx].bits += value;
    cmdWordArr[currOffset + idx].bits << BITS_IN_ADDRESS;
    insert_are(cmdWordArr[currOffset + idx].bits, RELOCATABLE);
    currOffset++;
    token = strtok(NULL, " \n");
    cmdWordArr[currOffset + idx].bits += atoi(token);
    return 2;
}*/

int code_register(int idx, char *operand, int operandNum, int currOffset){
    int registerIdx;
    cmdWordArr[idx].bits += REGISTER;
    cmdWordArr[idx].bits << BITS_IN_METHOD;

    registerIdx = operand[1] - '0'; /* convert argument[1] to int */
    printf("registerNum:%d\n", registerIdx);
    if(operandNum == 1){
        cmdWordArr[idx + currOffset].bits += registerIdx;
        cmdWordArr[idx + currOffset].bits << BITS_IN_REGISTER;
        cmdWordArr[idx + currOffset].bits << BITS_IN_REGISTER;
        cmdWordArr[idx].bits = insert_are(cmdWordArr[idx].bits, ABSOLUTE);
        return 1;
    }
    cmdWordArr[idx + currOffset].bits << BITS_IN_REGISTER;
    cmdWordArr[idx + currOffset].bits += registerIdx;
    cmdWordArr[idx + currOffset].bits << BITS_IN_REGISTER;
    cmdWordArr[idx + currOffset].bits = insert_are(cmdWordArr[idx].bits, ABSOLUTE);
    return 1;
}

int code_two_registers(int idx, char *src, char *dest, int currOffset)
{
    int registerIdx;
    cmdWordArr[idx].bits += REGISTER;
    cmdWordArr[idx].bits << BITS_IN_METHOD;
    cmdWordArr[idx].bits += REGISTER;
    cmdWordArr[idx].bits << BITS_IN_METHOD;
    cmdWordArr[idx].bits = insert_are(cmdWordArr[idx].bits, ABSOLUTE);

    registerIdx = src[1] - '0'; /* convert argument[1] to int */
    printf("registerNum:%d\n", registerIdx);
    cmdWordArr[idx + currOffset].bits += registerIdx;
    cmdWordArr[idx + currOffset].bits << BITS_IN_REGISTER;
    registerIdx = dest[1] - '0'; /* convert argument[1] to int */
    printf("registerNum:%d\n", registerIdx);
    cmdWordArr[idx + currOffset].bits += registerIdx;
    cmdWordArr[idx + currOffset].bits << BITS_IN_REGISTER;
    cmdWordArr[idx + currOffset].bits = insert_are(cmdWordArr[idx].bits, ABSOLUTE);

    return 1;
}

/****** FUNCTIONS WHICH DEAL WITH OUTPUT FILES ******/

int create_output_files(char *fileName){
    FILE *file;

    file = open_file(fileName, FILE_OBJECT);
    create_ob_file(file);

    /*if(entry_exists) {
        file = open_file(fileName, FILE_ENTRY);
        create_entry_file(file);
    }

    if(extern_exists){
        file = open_file(fileName, FILE_EXTERN);
        create_extern_file(file);
    }*/

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
        /*err = true;*/
        return NULL;
    }
    return file;
}


