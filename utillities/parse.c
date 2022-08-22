#include "parse.h"

void  parse_input(FILE *ptrFile){
    receivedLine receivedLine;
    init_line(&receivedLine);
    get_input(&receivedLine);
};

void init_line(receivedLine *receivedLine){
    int i;
    receivedLine->errorType = NO_ERROR;
    receivedLine->cmdIDX = NOT_FOUND;
    receivedLine->dst_operand = NO_OPERAND;
    receivedLine->src_operand = NO_OPERAND;
    receivedLine->numOfWords = 0;
    receivedLine->numOfOperands = 0;
    receivedLine->A_R_E = 0;
    for(i=0; i<CMD_LENGTH; i++){
        receivedLine -> operandsValues[0][i] = 0;
        receivedLine -> operandsValues[1][i] = 0;
        receivedLine -> operandsValues[2][i] = 0;
        receivedLine -> operandsValues[3][i] = 0;
        receivedLine -> operandsValues[4][i] = 0;
    }
    return;
}

void get_input(receivedLine *receivedLine){

}

void printError(int errorType){
    switch(errorType){
        case UND_CMD_NAME:
            printf("Undefined command name\n");
            break;
        case EXTRANEOUS_TEXT:
            printf("Extraneous text after end of command\n");
            break;
        case MULTIPLE_CON_COMMAS:
            printf("Multiple consecutive commas\n");
            break;
        case ILLEGAL_COMMA:
            printf("Illegal comma\n");
            break;
        case MISS_COMMA:
            printf("Missing comma\n");
            break;
        case MISS_PAR:
            printf("Missing argument\n");
            break;
        case UND_REGISTER_NAME:
            printf("Undefined register name\n");
            break;
        case NOT_LIST:
            printf("Argument is not a list of valid values\n");
            break;
        case NOT_INT:
            printf("Argument is not an integer\n");
            break;
    }
}
