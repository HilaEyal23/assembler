#ifndef _EXTERN_VARS_H
#define _EXTERN_VARS_H
#include "globals.h"
#include "structs.h"

extern int ic, dc;
extern int err;
extern boolean was_error;
extern const char base32[32];
extern word dirWordArr[2560];
extern word cmdWordArr[2560];
extern boolean entry_exists, extern_exists;
#endif /*_EXTERN_VARS_H*/

