#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "globals.h"
#include "structs.h"
#include "extern_vars.h"


/* Helper functions that are used for parsing tokens and navigating through them */
char *next_token_string(char *dest, char *line);
char *next_list_token(char *dest, char *line);
char *next_token(char *seq);
char *skip_spaces(char *ch);
int skipEmpty(char *line, int i);
void copy_token(char *dest, char *line);
boolean end_of_line(char *line); //
boolean toBeSkipped(char *line);

/* Helper functions that are used to determine types of tokens */
int find_idx(char *token, const char *arr[], int n); //
int find_command(char *token); //
int find_instruction(char *token); //
boolean is_str(char *string);
boolean is_int(char *seq); //
boolean is_register(char *token); //

/* Helper functions that are used for creating files and assigning required extensions to them */
char *create_file_name(char *original, int type);
FILE *open_file(char *filename, int type);
char *convert_to_base_32(unsigned int num);

/* Functions of external labels positions' linked list */
extPtr add_ext(extPtr *hptr, char *name, unsigned int reference);
void free_ext(extPtr *hptr);
void print_ext(extPtr h);

/* Functions that handle errors */
void printError(int line_num);
int has_error();

/* Helper functions for encoding and building words */
unsigned int extract_bits(unsigned int word, int start, int end);
void encode_to_instructions(unsigned int word);
unsigned int insert_are(unsigned int info, int are);
#endif /*UTILS_H*/


void init_received_line(receivedLine *receivedLine);