#ifndef _SECONDPASS_H
#define _SECONDPASS_H

#include "globals.h"
#include "utils.h"
#include "symbolList.h"
#include "externVars.h"

void second_pass(cmdLine cmdLines[], char *fileName, symbolNode *head);


/****** FUNCTIONS WHICH DEAL WITH ENCODING DIRECTIVE COMMANDS ******/




/****** FUNCTIONS WHICH DEAL WITH ENCODING INSTRUCTION COMMANDS ******/

int code_cmd_line(cmdLine *cmdPtr, int idx, symbolNode *head);
int code_cmd_operand(char *operand, int type, int idx, int currOffset, int operandNum, symbolNode *head, int lineNum);
int code_immediate(int idx, char *operand, int operandNum, int currOffset);
int code_direct(int idx, char *operand, int operandNum, symbolNode *head, int currOffset, int lineNum);
int code_relative(int idx, char *operand, int operandNum, symbolNode *head, int currOffset, int lineNum);
int code_two_registers(int idx, char *src, char *dest, int currOffset);
int code_register(int idx, char *operand, int operandNum, int currOffset);



/****** FUNCTIONS WHICH DEAL WITH OUTPUT FILES ******/

int create_output_files(char *filename);
void create_ob_file(FILE *file);
void create_entry_file(FILE *file);
void create_extern_file(FILE *file);
FILE *open_file(char *filename, int type);

#endif /*_SECONDPASS_H*/
