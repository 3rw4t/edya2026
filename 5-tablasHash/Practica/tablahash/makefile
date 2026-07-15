# Makefile para P4
# ejecutar desde la terminal escribiendo "make" 
# genera automáticamente el ejecutable del programa

FLAGS = -Wall -Wextra -Werror -std=c99

test: test.o tablahash.o contacto.o utils.o glist.o
	$(CC) -o $@ $^ $(FLAGS)

test.o: test.c tablahash.h contacto.h utils.h glist.o
	$(CC) -c $< $(FLAGS)

tablahash.o: tablahash.c tablahash.h
	$(CC) -c $< $(FLAGS)

contacto.o: contacto.c contacto.h
	$(CC) -c $< $(FLAGS)

utils.o: utils.c utils.h
	$(CC) -c $< $(FLAGS)

glist.o: glist.c glist.h
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm test

.PHONY = clean