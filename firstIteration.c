#import "firstIteration.h"
#include "globals.h"
#include "extern_vars.h"
int IC, DC;

void parse_line(receivedLine *receivedLine);

void first_iteration(FILE *fptr){
    receivedLine *receivedLine;
    int lineCtr = 0;
    IC = 0, DC = 0;

    while(fgets(receivedLine->line, MAX_LINE_LENGTH, fptr)){
        lineCtr++;
        if(!toBeSkipped(receivedLine->line)){
            init_received_line(receivedLine);
            parse_line(receivedLine);
            if(receivedLine->errorType != NO_ERROR)
                printError(lineCtr);
        }
    }
}

void parse_line(receivedLine *receivedLine){
    boolean isLabelDef = false;
    labelPtr head = NULL;
    char token[MAX_LINE_LENGTH];

    strcpy(receivedLine->line, skip_spaces(receivedLine->line));
    if(end_of_line(receivedLine->line))
        return;
    if(!isalpha(receivedLine->line[0]))
}

boolean is_label(char *token){
    int len = strlen(token);
    int i;

}