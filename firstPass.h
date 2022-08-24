#ifndef _FIRSTPASS_H
#define _FIRSTPASS_H

#include "symbolList.h"
#include "operation.h"
#include "structs.h"

/*#include "extern_vars.h"*/

/******MAIN FUNTIONS IN FIRST PASS******/
void first_pass(FILE *fp, char *fileName, symbolNode **head);
void get_command(char *p, char command[]);
int get_operand_type(char *op);
int get_direct_type(char *token, int lineNumber);
int find_L(int address1, int address2);
void add_IC_to_directs(symbolNode *head, int IC);

/******VALIDATION FUNCTIONS******/
int validate_instruction_form(char *line, int labelFlag, int lineNumber, int *arg1, int *arg2);
int validate_direct_form(char *line, int labelFlag, int lineNumber, int *DCL);
int validate_command(char *token, int lineNumber);
void validate_entry(int **DCL, int lineNumber, int labelFlag);
void validate_extern(int **DCl, int lineNumber, int labelFlag);
void validate_struct(int **DCL, int lineNumber, int labelFlag);
void validate_data(int **DCL, int lineNumber, int labelFlag);
void validate_string(int **DCL, int lineNumber, int labelFlag);
int check_extra_text(char *token, int lineNumber);
void validate_input_form(char input[], int labelFlag, int lineNumber);

/******PARSING FUNCTIONS******/
void skip_command(char **p);
void skip_spaces(char **p);
int check_comma(char c);
void skip_label(char **line);
void skip_token(char **p);
int skip_empty(char *line, int i);
int to_be_skipped(char line[]);
void copy_label_name(char *label, char *token);
boolean end_of_line(char *line);

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
