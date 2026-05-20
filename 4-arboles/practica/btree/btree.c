#include "btree.h"
#include <assert.h>
#include <stdlib.h>

#include <stdio.h>

struct _BTNodo {
  int dato;
  struct _BTNodo *left;
  struct _BTNodo *right;
};

struct _SNodo {
  struct _BTNodo* dato;
  struct _SNodo * sig;
};


typedef struct _Stack {
  struct _SNodo* nodo;
} *Stack;

Stack stack_crear (){
  Stack new = malloc(sizeof(struct _Stack));
  new->nodo = NULL;
  return new;
}

int stack_isEmpty(Stack pila){
  return pila->nodo == NULL;
}

void stack_push (Stack pila, struct _BTNodo* dato){
  struct _SNodo * new = malloc(sizeof(struct _SNodo));
  new->dato = dato;
  new->sig = pila->nodo;
  pila->nodo = new;
}
void stack_pop (Stack pila){
  if (stack_isEmpty(pila)) return;
  // struct _SNodo * temp =  pila->nodo;
  pila->nodo = pila->nodo->sig;
  // free(temp);
}

BTree stack_top(Stack pila){
  if (stack_isEmpty(pila)) return NULL;
  return pila->nodo->dato;
}

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear() { return NULL; }

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
    free(nodo);
  }
}

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo) { return nodo == NULL; }

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int dato, BTree left, BTree right) {
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato = dato;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  return nuevoNodo;
}

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,
                    FuncionVisitante visit) {
  if (!arbol) return;         

  if (orden == BTREE_RECORRIDO_POST ){  
    btree_recorrer(arbol->left, orden, visit);
    btree_recorrer(arbol->right, orden, visit);
    visit(arbol->dato);
  }

  if (orden == BTREE_RECORRIDO_IN ){  
    btree_recorrer(arbol->left, orden, visit);
    visit(arbol->dato);
    btree_recorrer(arbol->right, orden, visit);
  }

  if (orden == BTREE_RECORRIDO_PRE ){  
    
    /* 
    // version recursiva
    visit(arbol->dato);
    btree_recorrer(arbol->left, orden, visit);
    btree_recorrer(arbol->right, orden, visit);
    */
    
    // version iterativa
    Stack pila = stack_crear();
    stack_push(pila,arbol);
    for (;!stack_isEmpty(pila) ; stack_pop(pila)){
      for(;arbol; arbol= arbol->left){
        visit(arbol->dato);
        if (arbol->right) stack_push(pila, arbol->right);
      }
      arbol = stack_top(pila);
    }

  }
}


/*
  Retorna el número de nodos del árbol
*/
int btree_nnodos(BTree arbol){
  if (!arbol) return 0;
  return 1 + btree_nnodos(arbol->right) + btree_nnodos(arbol->left);
}

/*
  Devuelve 1 si el número dado se encuentra en el arbol, y 0 en caso contrario
*/
int btree_buscar(BTree arbol, int dato){
  if (!arbol) return 0;
  if (arbol->dato == dato) return 1;
  else return btree_buscar(arbol->left, dato) || btree_buscar(arbol->right, dato);
}

/*
  Devuelve un nuevo árbol que es una copia del árbol dado
*/
BTree btree_copiar(BTree arbol){
  if (!arbol) return NULL;

  struct _BTNodo * new = malloc(sizeof(struct _BTNodo));
  new->dato = arbol->dato;
  new->left = btree_copiar(arbol->left);
  new->right = btree_copiar(arbol->right);

  return new;
}

/*
  Devuelve la altura del árbol
*/
int btree_altura(BTree arbol){
  if (!arbol) return -1;
  if (btree_altura(arbol->left) > btree_altura(arbol->right)) return 1 + btree_altura(arbol->left);
  else return 1 + btree_altura(arbol->right);
}

/*
  Devuelve el número de nodos que se encuentran a la profundidad dada
*/
int btree_nnodos_profundidad(BTree arbol, int profundidad);