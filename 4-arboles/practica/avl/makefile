# Makefile para P4
# ejecutar desde la terminal escribiendo "make" 
# genera automáticamente el ejecutable del programa

FLAGS = -Wall -Wextra -Werror -std=c99

test: test.o avl.o
	$(CC) -o $@ $^ $(FLAGS)

test.o: test.c avl.h 
	$(CC) -c $< $(FLAGS)

avl.o: avl.c avl.h
	$(CC) -c $< $(FLAGS)
	
clean:
	rm *.o
	rm test

.PHONY = clean