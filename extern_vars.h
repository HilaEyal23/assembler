#ifndef _EXTERN_VARS_H
#define _EXTERN_VARS_H
#include "globals.h"
#include "structs.h"

extern int ic, dc;
extern int err;
extern boolean was_error;
extern labelPtr symbols_table;
extern extPtr ext_list;
extern const char base32[32];
extern const char *commands[];
extern const char *instructions[];
extern boolean entry_exists, extern_exists;
#endif /*_EXTERN_VARS_H*/
