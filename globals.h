#ifndef _GLOBALS_H
#define _GLOBALS_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


#define IC_INIT_VALUE 100
#define EMPTY_WORD 0
#define EXTERNAL_DEFAULT_ADDRESS 0
#define NO_ERROR 0
#define ERROR 1
#define NOT_FOUND -1
#define NO_OPERANDS 0
#define LAST_CHAR '\0'
#define DEFAULT_VAL '0'
#define TAB '\t'

#define MAX_LINE_LENGTH 81
#define MAX_NAME_LENGTH 31
#define REGISTER_NAME_LEN 3
#define CMD_LENGTH 4
#define BASE32_SEQUENCE_LENGTH 3
#define MAX_EXTENSION_LENGTH 5

#define OPERAND_TYPES_AMOUNT 5
#define MAX_NUM_OF_OPERANDS 2
#define REGISTER_AMOUNT 8
#define CMD_AMOUNT 16
#define ADDRESSING_METHOD_AMOUNT 4
#define INSTRUCTION_AMOUNT 5

#define BITS_IN_WORD 10
#define BITS_IN_OPCODE 4
#define BITS_IN_SRC 2
#define BITS_IN_DEST 2
#define BITS_IN_ARE 2

#define MACHINE_RAM 3000 /*to be checked*/


typedef enum boolean{false, true} boolean;
typedef enum flag{off, on} flag;

typedef enum addressingMethods{NO_OPERAND = -1, IMMEDIATE, DIRECT, RELATIVE, REGISTER, UNKNOWN} addressingMethods;
/*typedef enum operandType{NO_OPERAND = -1, INTEGER, LABEL, REGISTER, STRING, STRUCT, DATA} operandType;*/
typedef enum error{UND_CMD_NAME, EXTRANEOUS_TEXT, MULTIPLE_CON_COMMAS,ILLEGAL_COMMA, MISS_COMMA, MISS_PAR, UND_REGISTER_NAME, NOT_INT, NOT_LIST} error;
typedef enum cmdIdx{NOT_FOUND_OP = -1, MOV, CMP, ADD, SUB, NOT, CLR, LEA, INC, DEC, JMP, BNE, GET, PRN, JSR, RST, HLT} cmdIdx;
typedef enum instruction{NONE = -1, DATA, STRING, STRUCT, ENTRY, EXTERN, UNKNOWN_TYPE} instruction;
enum ARE {ABSOLUTE, EXTERNAL, RELOCATABLE};
enum filetypes {FILE_INPUT, FILE_OBJECT, FILE_ENTRY, FILE_EXTERN};



#endif /*_GLOBALS_H*/
