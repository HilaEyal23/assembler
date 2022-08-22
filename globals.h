#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


#define IC_INIT_VALUE 100
#define EMPTY_WORD 0
#define EXTERNAL_DEFAULT_ADDRESS 0
#define NO_ERRORS 0
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
#define ADDRESSING_METHOD_AMOUNT 6
#define INSTRUCTION_AMOUNT 5
#define ERRORS_AMOUNT 37

#define BITS_IN_WORD 10
#define BITS_IN_OPCODE 4
#define BITS_IN_METHOD 2
#define BITS_IN_ARE 2
#define BITS_IN_REGISTER 4
#define BITS_IN_ADDRESS 8

#define MACHINE_RAM 2560 /*to be checked*/



typedef enum boolean{false, true} boolean;

typedef enum flag{off, on} flag;

typedef enum addressingMethods{NO_OPERAND = -1, IMMEDIATE, DIRECT, RELATIVE, REGISTER, UNKNOWN} addressingMethods;

typedef enum error{NO_ERROR, SYNTAX_ERR, UND_CMD_NAME, UND_REGISTER_NAME, INVALID_LABEL_NAME, LABEL_CANT_BE_COMMAND, LABEL_CANT_BE_REGISTER,

                    EXTRANEOUS_TEXT, MULTIPLE_CON_COMMAS,ILLEGAL_COMMA, MISS_COMMA, MISS_PAR, NOT_INT, NOT_LIST, LABEL_ONLY, CMD_NOT_FOUND,

                    DIRECTIVE_NO_PARAMS, DIRECTIVE_INVALID_NUM_PARAMS, COMMAND_UNEXPECTED_CHAR, COMMAND_TOO_MANY_OPERANDS, COMMAND_INVALID_OPERANDS_METHODS,

                    COMMAND_INVALID_NUMBER_OF_OPERANDS,

                    STRING_TOO_MANY_OPERANDS, STRING_OPERAND_NOT_VALID, STRUCT_INVALID_STRING, 	

		    STRUCT_EXPECTED_STRING,EXPECTED_COMMA_BETWEEN_OPERANDS,STRUCT_INVALID_NUM,

                    STRUCT_TOO_MANY_OPERANDS, DATA_EXPECTED_NUM, DATA_EXPECTED_COMMA_AFTER_NUM, DATA_COMMAS_IN_A_ROW, DATA_UNEXPECTED_COMMA, COMMAND_INVALID_METHOD,

                    EXTERN_NO_LABEL, EXTERN_INVALID_LABEL, EXTERN_TOO_MANY_OPERANDS} error;

typedef enum cmdIdx{NOT_FOUND_OP = -1, MOV, CMP, ADD, SUB, NOT, CLR, LEA, INC, DEC, JMP, BNE, GET, PRN, JSR, RTS, HLT} cmdIdx;

typedef enum dirType{NONE = -1,DATA, STRING, STRUCT, ENTRY, EXTERN, CODE};

enum ARE {ABSOLUTE, EXTERNAL, RELOCATABLE};

enum filetypes {FILE_INPUT, FILE_OBJECT, FILE_ENTRY, FILE_EXTERN};

/*enum operands{IMMEDIATE_OP = 0, DIRECT_OP, STRUCT_OP, REGISTER_OP};*/

/*enum {NO_COLON, COLON};*/



#endif /*_GLOBALS_H*/