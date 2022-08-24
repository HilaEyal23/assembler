#include "operation.h"

static const struct  operationConsts{

    const char *name;
    int opcode;
    int operandNum;
    int sourceOperand;
    int destinationOperand;
} operationTable[] = {{"mov",MOV,2, IMMEDIATE_OP | DIRECT_OP | STRUCT_OP | REG_OP, DIRECT_OP | STRUCT_OP | REG_OP},
                      {"cmp",CMP,2, IMMEDIATE_OP | DIRECT_OP | STRUCT_OP | REG_OP, IMMEDIATE_OP  | DIRECT_OP| STRUCT_OP | REG_OP},
                      {"add",ADD,2, IMMEDIATE_OP | DIRECT_OP | STRUCT_OP | REG_OP, DIRECT_OP | STRUCT_OP | REG_OP},
                      {"sub",SUB,2, IMMEDIATE_OP | DIRECT_OP | STRUCT_OP | REG_OP, DIRECT_OP | STRUCT_OP | REG_OP},
                      {"not",NOT,1,0,  DIRECT_OP | STRUCT_OP | REG_OP},
                      {"clr",CLR,1,0,  DIRECT_OP | STRUCT_OP | REG_OP},
                      {"lea",LEA,2,    DIRECT_OP | STRUCT_OP , DIRECT_OP| STRUCT_OP | REG_OP},
                      {"inc",INC,1,0,  DIRECT_OP | STRUCT_OP | REG_OP},
                      {"dec",DEC,1,0,  DIRECT_OP | STRUCT_OP | REG_OP},
                      {"jmp",JMP,1,0,  DIRECT_OP | STRUCT_OP | REG_OP},
                      {"bne",BNE,1,0,  DIRECT_OP | STRUCT_OP | REG_OP},
                      {"get",GET,1,0,  DIRECT_OP | STRUCT_OP | REG_OP},
                      {"prn",PRN,1,0,  IMMEDIATE_OP  |DIRECT_OP | STRUCT_OP | REG_OP},
                      {"jsr",JSR,1,0,  DIRECT_OP | STRUCT_OP | REG_OP},
                      {"rts",RTS,0,0,0},
                      {"hlt",HLT,0,0,0}};





int is_operation(char *name) {

    int i = 0;

    while (i < NUM_OF_OPERATIONS) {


        if (strcmp(name,operationTable[i].name) == 0) {
            return  true;
        }
        i++;
    }
    return  false;

}


int get_operation_opcode(char *name){

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



int get_operand_num(char *name){

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


int get_src_operand(char *name){
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


int get_dest_operand(char *name){
    int i = 0;
    while (i < NUM_OF_OPERATIONS){
        if(strcmp(name,operationTable[i].name) == 0) {
            return operationTable[i].destinationOperand;
        }
        i++;
    }
    return -1;
}


