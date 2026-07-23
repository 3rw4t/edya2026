#include "glist.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Devuelve una lista vacía.
 */
GList glist_crear() { return NULL; }

/**
 * Destruccion de la lista.
 * destroy es una función que libera el dato almacenado.
 */
void glist_destruir(GList list, FuncionDestructora destroy) {
  GNode *nodeToDelete;
  while (list != NULL) {
    nodeToDelete = list;
    list = list->next;
    destroy(nodeToDelete->data);
    free(nodeToDelete);
  }
}

/**
 * Determina si la lista es vacía.
 */
int glist_vacia(GList list) { return (list == NULL); }

/**
 * Agrega un elemento al inicio de la lista.
 * copy es una función que retorna una copia física del dato.
 */
GList glist_agregar_inicio(GList list, void *data, FuncionCopia copy) {
  GNode *newNode = malloc(sizeof(GNode));
  assert(newNode != NULL);
  newNode->next = list;
  newNode->data = copy(data);
  return newNode;
}

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList list, FuncionVisitante visit) {
  for (GNode *node = list; node != NULL; node = node->next)
    visit(node->data);
}

/*
  Retorna el elemento si está en la lista, NULL si no
*/
GList glist_buscar(GList lista, void* dato, FuncionComparadora cmp){
  if(!dato) return NULL;
  for(;lista;lista =  lista->next) if (cmp(lista->data, dato) == 0) return lista;
  return NULL; 
}


GList glist_eliminar(GList lista, void * dato, FuncionComparadora cmp, FuncionDestructora destr){
  if(!lista)return NULL;
  if(!dato) return lista;

  if(cmp(lista->data, dato) == 0){
    destr(lista->data);
    
    GList temp = lista->next;
    free(lista);
    return temp;
  }
  lista->next = glist_eliminar(lista->next, dato, cmp, destr);
  return lista;
}
