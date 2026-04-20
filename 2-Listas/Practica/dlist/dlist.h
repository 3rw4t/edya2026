#ifndef __DLIST_H__
#define __DLIST_H__
#include <stddef.h>
typedef struct _DNodo {
    int dato;
    struct _DNodo *ant;
    struct _DNodo *sig;
} DNodo;

typedef struct {
   DNodo* primero;
   DNodo* ultimo; 
} DList;


// Devuelve NULL
DList* dlist_crear();


// Destruye la lista
void dlist_destruir(DList *lista);

// Agrega un elemento al inicio
DList* dlist_agregar_inicio (DList *lista, int dato);

DList *dlist_agregar_final (DList *lista, int dato);

void dlist_recorrer(DList *lista);



#endif /* __DLIST_H__ */