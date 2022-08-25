#ifndef _FIRSTPASS_H
#define _FIRSTPASS_H

#include "symbolList.h"
#include "operation.h"
#include "structs.h"

/*#include "extern_vars.h"*/

/******MAIN FUNTIONS IN FIRST PASS******/

/**
 * the first pass function.
 */
void first_pass(FILE *fp, char *fileName, symbolNode **head);
/**
 * gets the coammand.
 */
void get_command(char *p, char command[]);
/**
 * takes string and returns the operand type.
 */
int get_operand_type(char *op);
/**
 * takes string and returns the direction type line .data/.string...
 */
int get_direct_type(char *token, int lineNumber);
/**
 * finds the L that we need to add to the address.
 */
int find_L(int address1, int address2);
/**
 * add IC to all the directs so they will be after the commands in the ob file.
 */
void add_IC_to_directs(symbolNode *head, int IC);

/******VALIDATION FUNCTIONS******/

/**
 * validats instruction line form .
 */
int validate_instruction_form(char *line, int labelFlag, int lineNumber, int *arg1, int *arg2);

/**
 * validates direct line form.
 */
int validate_direct_form(char *line, int labelFlag, int lineNumber, int *DCL);

/**
 * cheks if command is ok.
 */
int validate_command(char *token, int lineNumber);

/**
 * validates entry line.
 */
void validate_entry(int **DCL, int lineNumber, int labelFlag);

/**
 * validates external line.
 */
void validate_extern(int **DCl, int lineNumber, int labelFlag);

/**
 * validates structure line.
 */
void validate_struct(int **DCL, int lineNumber, int labelFlag);

/**
 * validates data line.
 */
void validate_data(int **DCL, int lineNumber, int labelFlag);

/**
 * validates string line.
 */
void validate_string(int **DCL, int lineNumber, int labelFlag);

/**
 * checks for extra text after the end of the arguments.
 */
int check_extra_text(char *token, int lineNumber);

/**
 * validates general line form like commas label and more.
 */
void validate_input_form(char input[], int labelFlag, int lineNumber);

/******PARSING FUNCTIONS******/

/**
 * skipping the command.
 */
void skip_command(char **p);

/**
 * skipping spaces.
 */
void skip_spaces(char **p);

/**
 * checks for comma.
 */
int check_comma(char c);

/**
 * skips label word.
 */
void skip_label(char **line);

/**
 * skips simple token.
 */
void skip_token(char **p);

/**
 * skipping empty.
 */
int skip_empty(char *line, int i);

/**
 * checks if this line starts with ; or if its empty line.
 */
int to_be_skipped(char line[]);

/**
 * copys the label name from any token.
 */
void copy_label_name(char *label, char *token);

/**
 * frees and close the file.
 */
boolean end_of_line(char *line);

/******DETECTING FUNCTIONS******/

/**
 * checks if the token is label name or not.
 */
int is_label(char *token, int lineNumber);

/**
 * checks if the token is direct or not.
 */
int is_direct(char *token, int lineNumber);

/**
 * checks if string is number or not.
 */
int is_number(char *num);

/**
 * checks if token is an alpha word and does not have figits or symbols like @#$.
 */
int is_alpha_word(char *word);

/******DEBUG TOOLS******/

void print_cmdArray();
void print_cmd_line(cmdLine line);
void print_dirArray();
void print_dir_line(dirLine line);


#endif /*_FIRSTPASS_H*/
