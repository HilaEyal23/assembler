#ifndef _OPERATION_H
#define _OPERATION_H

#include <stdio.h>
#include <string.h>
#include "globals.h"


#define IMMEDIATE_OP 1    /*0001*/
#define DIRECT_OP 2   /*0010*/
#define STRUCT_OP 4    /*0100*/
#define REG_OP 8   /*1000*/
int is_operation(char *name);


int get_operation_opcode(char *name);


int get_operand_num(char *name);


int get_src_operand(char *name);


int get_dest_operand(char *name);




#endif /*_OPERATION_H*/
