#include "operationTable.h"

static const struct  operationConsts{

    const char *name;
    int opcode;
    int operandNum;
    int sourceOperand;
    int destinationOperand;
} operationTable[] = {{"mov",MOV,2, FIRST_ADDRESS | SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS, SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"cmp",CMP,2, FIRST_ADDRESS | SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS, FIRST_ADDRESS  | SECOND_ADDRESS| THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"add",ADD,2, FIRST_ADDRESS | SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS, SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"sub",SUB,2, FIRST_ADDRESS | SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS, SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"not",NOT,1,0,  SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"clr",CLR,1,0,  SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"lea",LEA,2,    SECOND_ADDRESS | THIRD_ADDRESS , SECOND_ADDRESS| THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"inc",INC,1,0,  SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"dec",DEC,1,0,  SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"jmp",JMP,1,0,  SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"bne",BNE,1,0,  SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"get",GET,1,0,  SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"prn",PRN,1,0,  FIRST_ADDRESS  |SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"jsr",JSR,1,0,  SECOND_ADDRESS | THIRD_ADDRESS | FOURTH_ADDRESS},
                      {"rts",RTS,0,0,0},
                      {"hlt",HLT,0,0,0}};





int isOperationName(char *name) {

    int i = 0;

    while (i < NUM_OF_OPERATIONS) {


        if (strcmp(name,operationTable[i].name) == 0) {
            return  true;
        }
        i++;
    }
    return  false;

}


int getOperationOpcode(char *name){

    int i = 0;
    int error = -1;

    while(i < NUM_OF_OPERATIONS){
        if(strcmp(name,operationTable[i].name) == 0){
            return operationTable[i].opcode;
        }
        i++;
    }

    return error;
}



int getOperandNum(char *name){

    int i = 0;
    int error = -1;

    while(i < NUM_OF_OPERATIONS){
        if(strcmp(name,operationTable[i].name) == 0){
            return operationTable[i].operandNum;
        }
        i++;
    }

    return error;
}


int getSourceOperand(char *name){
    int i = 0;
    int error = -1;


    while (i < NUM_OF_OPERATIONS){
        if(strcmp(name,operationTable[i].name) == 0) {
            return operationTable[i].sourceOperand;
        }
        i++;
    }
    return error;

}


int getDestinationOperand(char *name){
    int i = 0;
    int error = -1;


    while (i < NUM_OF_OPERATIONS){
        if(strcmp(name,operationTable[i].name) == 0) {
            return operationTable[i].destinationOperand;
        }
        i++;
    }
    return error;
}


