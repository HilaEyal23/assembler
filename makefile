FLAGS = -ansi -Wall -pedantic

assembler: main.o firstPass.o preprocessor.o macro_list.o symbolList.o assembler.o entryAndExtern.o operation.o secondPass.o utils.o
	gcc -g $(FLAGS) macro_list.o preprocessor.o firstPass.o assembler.o symbolList.o operation.o secondPass.o entryAndExtern.o utils.o main.o -o assembler -lm
symbolList.o: symbolList.c
	gcc -c  $(FLAGS) symbolList.c -o symbolList.o
firstPass.o: firstPass.c
	gcc -c $(FLAGS) firstPass.c -o firstPass.o
operation.o: operation.c
	gcc -c $(FLAGS) operation.c -o operation.o
secondPass.o: secondPass.c
	gcc -c $(FLAGS) secondPass.c -o secondPass.o 
utils.o: utils.c
	gcc -c $(FLAGS) utils.c -o utils.o -lm
main.o: main.c
	gcc -c $(FLAGS) main.c -o main.o 
preprocessor.o: preprocessor.c
	gcc -c $(FLAGS) preprocessor.c -o preprocessor.o 
macro_list.o: macro_list.c
	gcc -c $(FLAGS) macro_list.c -o macro_list.o 
assembler.o: assembler.c
	gcc -c $(FLAGS) assembler.c -o assembler.o 
entryAndExtern.o: entryAndExtern.c
	gcc -c $(FLAGS) entryAndExtern.c -o entryAndExtern.o 

