#ifndef _SECONDPASS_H
#define _SECONDPASS_H
#include "globals.h"
#include "utils.h"
#include "symbolList.h"
#include "externVars.h"
#include "operation.h"
#include "entryAndExtern.h"
void second_pass(cmdLine cmdLines[], dirLine dirLines[], char *fileName, symbolNode *head, entry *entHead, external *extHead);

/****** FUNCTIONS WHICH DEAL WITH ENCODING INSTRUCTION COMMANDS ******/

/*
* This function encodes opcode and manipulates the functions required for instruction-line coding according to it's operands. 
*@param cmdPtr - pointer to the parsed line which we want to encode.
*@param idx - index of the next empty cell in the instruction binary-code array.
*@param head - a pointer to the symbol-list head.
*@return - index of the next empty cell in the instruction binary-code array.
*/
int code_cmd_line(cmdLine *cmdPtr, int idx, symbolNode *head);

/*
* This function manipulates the functions required for given operand coding according to it's type.
*@param operand - the operand which we want to encode.
*@param type - the given operand type.
*@param idx - index of the next empty cell in the instruction binary-code array.
*@param head - a pointer to the symbol-list head.
*@return - index of the next empty cell in the instruction binary-code array.
*/
int code_cmd_operand(char *operand, int type, int idx, int currOffset, int operandNum, symbolNode *head, int lineNum, int numOfOperands);

/*
* This function encodes operand whitch it's addressing method is immediate.
*/
int code_immediate(int idx, char *operand, int operandNum, int currOffset, int numOfOperands);

/*
* This function encodes operand whitch it's addressing method is direct.
*/
int code_direct(int idx, char *operand, int operandNum, symbolNode *head, int currOffset, int lineNum, int numOfOperands);

/*
* This function encodes operand whitch it's addressing method is relative.
*/
int code_relative(int idx, char *operand, int operandNum, symbolNode *head, int currOffset, int lineNum, int numOfOperands);

/*
* This function encodes an instruction-line which it's operands are two registers.
*/
int code_two_registers(int idx, char *src, char *dest, int currOffset);

/*
* This function encodes operand whitch it's addressing method is register.
*/
int code_register(int idx, char *operand, int operandNum, int currOffset, int numOfOperands);







/****** FUNCTIONS WHICH DEAL WITH ENCODING DIRECTIVE COMMANDS ******/

/*
* This function manipulates the functions required for data-line coding according to it's type. 
*@param dirPtr - pointer to the parsed line which we want to encode.
*@param idx - index of the next empty cell in the instruction binary-code array.
*@return - index of the next empty cell in the instruction binary-code array.
*/
int code_dir_line(dirLine *dirPtr, int idx);

/*
* This function encodes a data-line which it's type is .data.
*/
int code_data_dir(char operand[][MAX_NAME_LENGTH], int numOfOperands, int idx);

/*
* This function encodes a data-line which it's type is .string.
*/
int code_string_dir(char operand[][MAX_NAME_LENGTH], int idx, int structIdx);

/*
* This function encodes a data-line which it's type is .struct.
*/
int code_struct_dir(char operand[][MAX_NAME_LENGTH], int idx);







/****** FUNCTIONS WHICH DEAL WITH OUTPUT FILES ******/

/*
* This function manipulates the functions required for creating output files. 
*@param fileName - the name of the original file.
*@param head - a pointer to the symbol-list head.
*@param entHead - a pointer to the entry-list head.
*@param extHead - a pointer to the extern-list head.
*@return - index of the next empty cell in the instruction binary-code array.
*/
int create_output_files(char *filename, symbolNode *head, entry *entHead, external *extHead);

/*
* This function manipulates the functions required for converting the binary code to base 32 and outputs it into an object file. 
*/
void create_ob_file(FILE *file);

/*
* This function manipulates the functions required for converting the entries binary code to base 32 and outputs it into an entry file. 
*/
void create_entry_file(FILE *file, symbolNode *head, entry *entHead);

/*
* This function manipulates the functions required for converting the externs binary code to base 32 and outputs it into an extern file. 
*/
void create_extern_file(FILE *file, external *extHead);
FILE *open_file(char *filename, int type);

#endif
