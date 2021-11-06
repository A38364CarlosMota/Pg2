##############MakeFile#######################

all: primeira

primeira: primeira.c
		gcc -o 1 primeira.c -Wall 
segundo: segundo.c
		gcc -o 2 segundo.c -Wall
terceiro:
		gcc -o 3 terceiro.c -Wall
		
clean:
	rm *.o
