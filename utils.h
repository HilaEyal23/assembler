#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"

#define MAX_LINE_LENGTH 81
#define true 1
#define false 0
#define TAB '\t'

int is_cmd(char str[]);
int is_int(char s[]);
/*void skipEmpty(char line[]);*/
int toBeSkipped(char line[]);
int skipEmpty(char *line, int i);

#endif /*UTILS_H*/
