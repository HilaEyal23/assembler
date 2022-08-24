#include "globals.h"
#include "structs.h"
#include "utils.h"
#include "firstPass.h"
#include "preprocessor.h"

void first_pass(FILE *fp, char *fileName, symbolNode **head);
void second_pass(cmdLine cmdLines[], char *fileName, symbolNode *head);
void reset_global_vars();
int assembler(int argc, char **argv);
