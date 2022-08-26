#include "globals.h"
#include "structs.h"
#include "utils.h"
#include "firstPass.h"
#include "preprocessor.h"
#include "entryAndExtern.h"


void second_pass(cmdLine cmdLines[], dirLine dirLines[], char *fileName, symbolNode *head, entry *entHead, external *extHead);
void reset_global_vars();
int assembler(int argc, char **argv);
