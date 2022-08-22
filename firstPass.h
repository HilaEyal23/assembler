#ifndef _FIRSTPASS_H
#define _FIRSTPASS_H

#include "symbolList.h"
#include "operationTable.h"
#include "structs.h"

/*#include "extern_vars.h"*/

/******MAIN FUNTIONS IN FIRST PASS******/
void first_pass(FILE *fp, char *fileName);
int get_cmd_IDX(char str[]);
void get_command(char *p, char command[]);
int get_operand_type(char *op);
int get_direct_type(char *token, int lineNumber);
int find_L(int address1, int address2);

/******VALIDATION FUNCTIONS******/
int validate_instruction_form(char *line, int labelFlag, int lineNumber, int *arg1, int *arg2);
int validate_direct_form(char *line, int labelFlag, int lineNumber);
int validate_input_form(char *line, int min_args);
int validate_command(char *token, int lineNumber);

/******PARSING FUNCTIONS******/
void skip_command(char **p);
void skip_spaces(char **p);
int check_comma(char c);
void skip_label(char **line);
void skip_token(char **p);
int skip_empty(char *line, int i);
int to_be_skipped(char line[]);
void copy_label_name(char *label, char *token);

/******DETECTING FUNCTIONS******/
int is_label(char *token, int lineNumber);
int is_direct(char *token, int lineNumber);
int is_number(char *num);
int is_alpha_word(char *word);

/******DEBUG TOOLS******/
void print_cmdArray();
void print_cmd_line(cmdLine line);
void print_dirArray();
void print_dir_line(dirLine line);


#endif /*_FIRSTPASS_H*/
