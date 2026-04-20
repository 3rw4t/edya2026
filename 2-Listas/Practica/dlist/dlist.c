#include "dlist.h"
#include <stdlib.h>
#include <stdio.h>


DList * dlist_crear (){
    return NULL;
}

void dlist_destruir (DList *lista){
    if(!lista) return;
    DNodo * temp;
    while (lista->primero){
        temp = lista->primero;
        lista->primero = (lista->primero)->sig;
        free(temp);
    }
}

DList* dlist_agregar_inicio(DList *lista,int dato){
    DNodo * nuevoNodo = malloc(sizeof(DNodo));
    nuevoNodo->dato = dato;
    nuevoNodo->ant = NULL;
    if (!lista){
        DList * nuevaLista = malloc(sizeof(DList));
        nuevaLista->primero = nuevoNodo;
        nuevaLista->ultimo = nuevoNodo;

        nuevoNodo->sig = NULL;

        return nuevaLista;
    }
    lista->primero->ant = nuevoNodo;
    nuevoNodo->sig = lista->primero;
    lista->primero = nuevoNodo;
    return lista;

}

DList *dlist_agregar_final (DList *lista, int dato){
    DNodo * nuevoNodo = malloc(sizeof(DNodo));
    nuevoNodo->dato = dato;
    nuevoNodo->sig = NULL;
    if(!lista){
        DList * nuevaLista = malloc(sizeof(DList));
        nuevaLista->primero = nuevoNodo;
        nuevaLista->ultimo = nuevoNodo;

        nuevoNodo->ant = NULL;

        return nuevaLista;
    }
    
    lista->ultimo->sig = nuevoNodo;
    nuevoNodo->ant = lista->ultimo;
    lista->ultimo = nuevoNodo;
    return lista;
}

void dlist_recorrer(DList *lista){
    int contador = 0;
    DNodo * temp = lista->primero;
    for(; temp; temp = temp->sig, contador++) printf ("dato n°%d= %d\n", contador,temp->dato);
};
