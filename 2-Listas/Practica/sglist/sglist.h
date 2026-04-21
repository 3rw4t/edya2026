#ifndef __SGLIST_H__
#define __SGLIST_H__

#include <stddef.h>

typedef struct _SGNodo{
    void *dato;
    struct _SGNodo *sig;
} SGNodo;

typedef SGNodo *SGList;

typedef void (*FuncionVisitante)(void *dato);
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
typedef void *(*FuncionCopia)(void * dato);
typedef void (*FuncionDestructora)(void * dato);
// Crea una nueva sglist vacía
SGList sglist_crear();

// destruye todos los elementos de una sglist
void sglist_destruir(SGList lista, FuncionDestructora destruir);

// devuelve 1 si está vacía, 0 si no.
int sglist_vacia(SGList lista);

// aplica la función visitante a todos los elementos de la lista
void sglist_recorrer(SGList lista, FuncionVisitante visitante);

// inserta un elemento en la lista ordenada
SGList sglist_insertar(SGList lista, void * data, FuncionCopia copiar, FuncionComparadora comparar);

#endif //__SGLIST_H__