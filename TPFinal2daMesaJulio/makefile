# ejecutar desde la terminal escribiendo "make" 
# genera automáticamente el ejecutable del programa

FLAGS = -Wall -Wextra -Werror -std=c99

programa: main.o inventario.o tablahash.o glist.o avl.o
	$(CC) -o $@ $^ $(FLAGS)

main.o: main.c tablahash.o inventario.o glist.o avl.o
	$(CC) -c $< $(FLAGS)

inventario.o: inventario/inventario.c inventario/inventario.h 
	$(CC) -c $< $(FLAGS)

tablahash.o: tablahash/tablahash.c tablahash/tablahash.h 
	$(CC) -c $< $(FLAGS)

glist.o: glist/glist.c glist/glist.h
	$(CC) -c $< $(FLAGS)

avl.o: avl/avl.c avl/avl.h
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm programa

.PHONY = clean