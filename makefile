FLAGS = -ansi -Wall -pedantic

firstPass: firstPass.o symbolList.o operationTable.o
	gcc -g $(FLAGS) firstPass.o symbolList.o operationTable.o  -o firstPass
symbolList.o: symbolList.c
	gcc -c  $(FLAGS) symbolList.c -o symbolList.o
firstPass.o: firstPass.c
	gcc -c $(FLAGS) firstPass.c -o firstPass.o
operationTable.o: operationTable.c
	gcc -c $(FLAGS) operationTable.c -o operationTable.o
