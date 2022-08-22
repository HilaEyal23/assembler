#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "globals.h"
#include "structs.h"
#include "externVars.h"

char *create_file_name(char *original, int type);
FILE *open_file(char *filename, int type);

unsigned int extract_bits(unsigned int word, int start, int end);
char *convert_to_base_32(unsigned int num);


unsigned int insert_are(unsigned int info, int are);
#endif /*UTILS_H*/


