#include "slist.h"
#include <stdlib.h>
#include <stdio.h>
SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) {
  return lista == NULL;
}

SList slist_agregar_final(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  SList nodo = lista;
  for (;nodo->sig != NULL;nodo = nodo->sig);
  /* ahora 'nodo' apunta al ultimo elemento en la lista */

  nodo->sig = nuevoNodo;
  return lista;
}

SList slist_agregar_inicio(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

void slist_recorrer(SList lista, FuncionVisitante visit) {
  //for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig)
  //  visit(nodo->dato);
  if (lista) {
    visit(lista->dato);
    slist_recorrer(lista->sig, visit);
  }
}

SList slist_partir (SList lista){
  // Si la lista tiene 0 o 1 elementos, devuelve NULL
  if (!lista || !lista->sig) return NULL;

  // Se recorre la lista con 2 punteros, uno que avanza de a un elemento por iteración (p1),
  // y otro que avanza de a dos (p2), pero nunca toma el elemento NULL.
  // Finalmente, se devuelve la direccion del siguiente elemento del puntero más lento, es decir, p1->sig
  SList p1, p2;
  for (p1 = lista, p2 = lista; p2->sig && p2->sig->sig; p1 = p1->sig, p2 = p2->sig->sig);

  // guardamos la dirección siguiente a p1 para devolver su valor original antes de setearlo a NULL 
  p2 = p1->sig;
  p1->sig = NULL;
  return p2;
}

int slist_longitud (SList lista){
  int contador = 0;
  // incremento el contador en tanto lista != NULL
  for ( ; lista; lista = lista->sig) contador++;
  return contador;
}


SList slist_concatenar (SList lista1, SList lista2){
  SList temp = lista1;
  for (; temp->sig; temp = temp->sig);
  temp->sig = lista2;
  return lista1;
}

void slist_insertar(SList lista, int dato, int posicion){
  
  if (!(lista||posicion)){
    SNodo* nuevoNodo = malloc(sizeof(SNodo));
    nuevoNodo->sig = lista;
    nuevoNodo->dato = dato;
    lista = nuevoNodo;
  }


}
