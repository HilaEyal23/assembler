FLAGS = -ansi -Wall -pedantic

preprocessor: preprocessor.o macroList.o utils.o
	gcc -g $(FLAGS) preprocessor.o macroList.o utils.o -o preprocessor 
preprocessor.o: preprocessor.c
	gcc -c $(FLAGS) preprocessor.c -o preprocessor.o 
utils.o: utils.c
	gcc -c $(FLAGS) utils.c -o utils.o 
macroList.o: macroList.c
	gcc -c $(FLAGS) macroList.c -o macroList.o
