# Makefile para P4
# ejecutar desde la terminal escribiendo "make" 
# genera automáticamente el ejecutable del programa

FLAGS = -Wall -Wextra -Werror -std=c99

test: test.o bstree.o
	$(CC) -o $@ $^ $(FLAGS)

test.o: test.c bstree.h 
	$(CC) -c $< $(FLAGS)

bstree.o: bstree.c bstree.h
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm test

.PHONY = clean