FLAGS = -ansi -Wall -pedantic

main: main.o firstPass.o symbolList.o operationTable.o secondPass.o utils.o
	gcc -g $(FLAGS) firstPass.o symbolList.o operationTable.o secondPass.o utils.o main.o -o main -lm
symbolList.o: symbolList.c
	gcc -c  $(FLAGS) symbolList.c -o symbolList.o
firstPass.o: firstPass.c
	gcc -c $(FLAGS) firstPass.c -o firstPass.o
operationTable.o: operationTable.c
	gcc -c $(FLAGS) operationTable.c -o operationTable.o
secondPass.o: secondPass.c
	gcc -c $(FLAGS) secondPass.c -o secondPass.o 
utils.o: utils.c
	gcc -c $(FLAGS) utils.c -o utils.o -lm
main.o: main.c
	gcc -c $(FLAGS) main.c -o main.o 
