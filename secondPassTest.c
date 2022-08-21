#include "globals.h"
#include "utils.h"
/*#include "symbolList.h"*/
#include "externVars.h"

word cmdWordArr[2560];
int ic, dc;

void secondIteration(cmdLine cmdLines[]);
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

int main(){
    cmdLine cmdArr[20];
    cmdLine line1;
    cmdLine line2;
    cmdLine line3;
    cmdLine line4;
    cmdLine line5;

    line1.cmdIDX = PRN;
    line1.numOfOperands = 1;
    line1.src = "5";
    line1.srcType = IMMEDIATE;


    line2.cmdIDX = PRN;
    line2.numOfOperands = 1;
    line2.src = "-5";
    line2.srcType = IMMEDIATE;

    line5.cmdIDX = NO_CMD;


    line3.cmdIDX = SUB;
    line3.numOfOperands = 2;
    line3.src = "r1";
    line3.dest = "r4";
    line3.srcType = REGISTER;
    line3.destType = REGISTER;


    line4.cmdIDX = ADD;
    line4.numOfOperands = 2;
    line4.src = "5";
    line4.dest = "r2";
    line4.srcType = IMMEDIATE;
    line4.destType = REGISTER;

    cmdArr[1] = line1;
    cmdArr[2] = line2;
    cmdArr[3] = line3;
    cmdArr[4] = line4;
    cmdArr[5] = line5;
    secondIteration(&cmdArr[1]);
    
    return 0;
}

void secondIteration(cmdLine cmdLines[])
{
    cmdLine *cmdPtr = &cmdLines[0];
    int idx = 0;
    const char base32[32] = {
        '!', '@', '#', '$', '%', '^', '&', '*',
        '<','>', 'a', 'b', 'c','d', 'e', 'f',
        'g','h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p','q', 'r', 's', 't', 'u', 'v'
    };


    while(cmdPtr->cmdIDX != NO_CMD){ /*encodes instruction commands*/
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
            offset += code_cmd_operand(cmdPtr->src, cmdPtr->srcType, idx, offset, 1, cmdPtr->lineNum);
            return idx + offset;
        case 2:
	    if(cmdPtr->srcType == REGISTER && cmdPtr->destType == REGISTER){
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
        case IMMEDIATE:
            return code_immediate(idx, operand, operandNum, currOffset);
       /* case DIRECT:
            return code_direct(idx, operand, operandNum, currOffset);
        case RELATIVE:
            return code_relative(idx, operand, operandNum, currOffset, lineNum);*/
        case REGISTER:
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
