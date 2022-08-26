#ifndef _OPERATION_H
#define _OPERATION_H

#include <stdio.h>
#include <string.h>
#include "globals.h"


/**
 * cheks if token is operation or not.
 */
int is_operation(char *name);

/**
 * gets the operation opcode.
 */
int get_operation_opcode(char *name);

/**
 * returns how many operands the command should get.
 */
int get_operand_num(char *name);

/**
 * returns the type of the source operand.
 */
int get_src_operand(char *name);

/**
 * returns the type of the destination operand.
 */
int get_dest_operand(char *name);




#endif /*_OPERATION_H*/
