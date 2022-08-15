#ifndef _FIRSTPASS_H
#define _FIRSTPASS_H

#include "globals.h"
#include "symbolList.h"

void init_line(receivedLine *receivedLine);
void  parse_input(FILE *ptrFile);
void get_input(receivedLine *receivedLine);

int is_data_ins();
int errors_found();
int update_symbols_list();
int is_label_def();
int is_ext_or_ent();
int is_ext();
int is_symbol_def();

#endif /*_FIRSTPASS_H*/
