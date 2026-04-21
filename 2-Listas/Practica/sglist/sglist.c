#include "sglist.h"
#include <stdlib.h>
#include <stdio.h>

SGList sglist_crear(){
    return NULL;
}

void sglist_destruir(SGList lista, FuncionDestructora destruir){
    SGNodo * temp;
    while (lista){
        temp = lista;
        lista = lista->sig;
        destruir(temp->dato);
    }
}

// devuelve 1 si está vacía, 0 si no.
int sglist_vacia(SGList lista){
    if (!lista) return 1;
    return 0;
}

// aplica la función visitante a todos los elementos de la lista
void sglist_recorrer(SGList lista, FuncionVisitante visitante){
    while(lista){
        visitante(lista->dato);
        lista = lista->sig;
    }
}

// inserta un elemento en la lista ordenada
SGList sglist_insertar(SGList lista, void * data, FuncionCopia copiar, FuncionComparadora comparar){
    SGNodo * nuevo = malloc(sizeof(SGNodo));
    nuevo->dato = copiar(data);
    
    // Caso 1: Lista vacía o el dato va al principio
    // comparar(data, lista->dato) < 0 (o lo que devuelva tu función para "menor que")
    if (sglist_vacia(lista) || comparar(data, lista->dato) < 0) {
        nuevo->sig = lista;
        return nuevo;
    }

    // Caso 2: Insertar en el medio o al final
    SGNodo * ant = lista;
    SGNodo * actual = lista->sig;

    // Recorremos mientras el dato a insertar sea "mayor" que el del nodo actual
    while (actual != NULL && comparar(data, actual->dato) > 0) {
        ant = actual;
        actual = actual->sig;
    }

    // Insertamos entre 'ant' y 'actual'
    nuevo->sig = actual;
    ant->sig = nuevo;
    

    return lista;
   
}
