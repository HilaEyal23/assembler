FLAGS = -ansi -Wall -pedantic

preprocessor: preprocessor.o macro_list.o utils.o
	gcc -g $(FLAGS) preprocessor.o macro_list.o utils.o -o preprocessor 
preprocessor.o: preprocessor.c
	gcc -c $(FLAGS) preprocessor.c -o preprocessor.o 
utils.o: utils.c
	gcc -c $(FLAGS) utils.c -o utils.o 
macro_list.o: utillities/macro_list.c
	gcc -c $(FLAGS) utillities/macro_list.c -o macro_list.o

