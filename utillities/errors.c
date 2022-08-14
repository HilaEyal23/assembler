#include "errors.h"

void alert_error(int error){
	printf("error: ");
	switch(error)
	{
		case UF_MAT_NAME:
			printf("Undefined matrix name");
			break;

		case UF_CMD_NAME:
			printf("Undefined command name");
			break;

		case ARG_N_REAL_NUM:
			printf("Argument is not a real number");
			break;

		case EXTRA_TEXT:
			printf("Extraneous text after end of command ");
			break;

		case MISS_ARG:
			printf("Missing argument");
			break;

		case MISS_COMMA:
		  	printf("Missing comma");
			break;

		case ILLEGAL_COMMA:
			printf("Illegal comma");
			break;
		case MULT_CONSEC_COMMA:
			printf("Multiple consecutive commas");
			break;
		case ARG_N_SCALAR:
			printf("Argument is not a scalar");
			break;	
		case ALLOC_FAILD:
			printf("Allocation faild");
			break;
	}
	printf("\n");
	return;
}