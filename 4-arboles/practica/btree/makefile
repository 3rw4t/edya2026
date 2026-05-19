# Makefile para P4
# ejecutar desde la terminal escribiendo "make" 
# genera automáticamente el ejecutable del programa

FLAGS = -Wall -Wextra -Werror -std=c99

test: test.o btree.o
	$(CC) -o $@ $^ $(FLAGS)

test.o: test.c btree.h 
	$(CC) -c $< $(FLAGS)

btree.o: btree.c btree.h
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm test

.PHONY = clean