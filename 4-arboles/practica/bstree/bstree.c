#include "bstree.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Estructura del nodo del arbol de busqueda binaria.
 * Tiene un puntero al dato (dato),
 * un puntero al nodo raiz del subarbol izquierdo (izq),
 * y un puntero al nodo raiz del subarbol derecho (der).
 */
struct _BST_Nodo {
  void *dato;
  struct _BST_Nodo *izq, *der;
};

/**
 * bstee_crear: Retorna un arbol de busqueda binaria vacio
 */
BSTree bstee_crear() { return NULL; }

/**
 * bstree_destruir: Destruye el arbol y sus datos
 */
void bstree_destruir(BSTree raiz, FuncionDestructora destr) {
  if (raiz != NULL) {
    bstree_destruir(raiz->izq, destr);
    bstree_destruir(raiz->der, destr);
    destr(raiz->dato);
    free(raiz);
  }
};

/**
 * bstree_buscar: Retorna 1 si el dato se encuentra y 0 en caso
 * contrario
 */
int bstree_buscar(BSTree raiz, void *dato, FuncionComparadora comp) {
  if (raiz == NULL)
    return 0;
  else if (comp(dato, raiz->dato) == 0) // raiz->dato == dato
    return 1;
  else if (comp(dato, raiz->dato) < 0) // dato < raiz->dato
    return bstree_buscar(raiz->izq, dato, comp);
  else // raiz->dato < dato
    return bstree_buscar(raiz->der, dato, comp);
}

/**
 * bstree_insertar: Inserta un dato no repetido en el arbol, manteniendo la
 * propiedad del arbol de busqueda binaria
 */
BSTree bstree_insertar(BSTree raiz, void *dato, FuncionCopiadora copia,
                       FuncionComparadora comp) {
  if (raiz == NULL) { // insertar el dato en un nuevo nodo
    struct _BST_Nodo *nuevoNodo = malloc(sizeof(struct _BST_Nodo));
    assert(nuevoNodo != NULL);
    nuevoNodo->dato = copia(dato);
    nuevoNodo->izq = nuevoNodo->der = NULL;
    return nuevoNodo;
  } else if (comp(dato, raiz->dato) < 0) // dato < raiz->dato
    raiz->izq = bstree_insertar(raiz->izq, dato, copia, comp);
  else if (comp(dato, raiz->dato) > 0) // raiz->dato < dato
    raiz->der = bstree_insertar(raiz->der, dato, copia, comp);
  // si el dato ya se encontraba, no es insertado
  return raiz;
}

/**
 * bstree_recorrer: Recorrido DSF del arbol
 */
void bstree_recorrer(BSTree raiz, BSTreeRecorrido orden,
                     FuncionVisitanteExtra visita, void *extra) {
  if (raiz != NULL) {
    if (orden == BTREE_RECORRIDO_PRE)
      visita(raiz->dato, extra);
    bstree_recorrer(raiz->izq, orden, visita, extra);
    if (orden == BTREE_RECORRIDO_IN)
      visita(raiz->dato, extra);
    bstree_recorrer(raiz->der, orden, visita, extra);
    if (orden == BTREE_RECORRIDO_POST)
      visita(raiz->dato, extra);
  }
}

/*
  Elimina un elemento del árbol. El árbol resultante es ABB
*/
BSTree bstree_eliminar(BSTree arbol, void *dato, FuncionComparadora cmp, FuncionDestructora destr){
  if (!arbol) return arbol;

  if (cmp(arbol->dato, dato) == 0) {

    if (!arbol->izq && !arbol->der){
      destr(arbol->dato);
      free(arbol);
      return NULL;
    }else if (arbol->izq && arbol->der){

      struct _BST_Nodo *temp = arbol->izq;

      for (;temp->der; temp = temp->der);

      void * dato_a_destruir = arbol->dato; // para no romper la referencia directa

      arbol->dato = temp->dato;

      arbol->izq = bstree_eliminar (arbol->izq, dato_a_destruir, cmp, destr);
      return arbol;
    }else if (arbol->izq) {

      destr(arbol->dato);
      struct _BST_Nodo* temp = arbol->izq;
      free(arbol);
      return temp;
    }else{

      destr(arbol->dato);
      struct _BST_Nodo* temp = arbol->der;
      free(arbol);
      return temp;
    }
    

  }else if (cmp(arbol->dato, dato) < 0){

    arbol->der = bstree_eliminar(arbol->der, dato, cmp, destr);
  
  }else{
    arbol->der = bstree_eliminar(arbol->izq, dato, cmp, destr);

  } 
  return 0;
}

int btree_nnodos(BSTree arbol){
  if (!arbol) return 0;
  return 1 + btree_nnodos(arbol->izq) + btree_nnodos(arbol->der);
}

void* bstree_k_esimo_menor(BSTree arbol, int k) {
    if (arbol == NULL || k <= 0) return NULL;

    // 1. Buscar en el subárbol izquierdo
    void *izq = bstree_k_esimo_menor(arbol->izq, k);
    
    // Si 'izq' no es NULL, significa que el nodo ya fue encontrado 
    // en el subárbol izquierdo. Lo propagamos hacia arriba.
    if (izq != NULL) return izq;

    // ¿Cómo se enteró esta llamada de cuántos nodos se visitaron a la izquierda?
    // Contamos cuántos nodos hay en el subárbol izquierdo para restárselos a nuestro k.
    // (Nota: btree_nnodos es la función que ya tenías programada en tu archivo)
    int nodos_izq = btree_nnodos(arbol->izq);
    k = k - nodos_izq;

    // 2. Procesar la raíz actual
    if (k == 1) {
        return arbol->dato; // ¡Este es el k-ésimo menor!
    }

    // 3. Buscar en el subárbol derecho
    // Le restamos 1 a k (por la raíz que acabamos de descartar)
    return bstree_k_esimo_menor(arbol->der, k - 1);
}

// Función auxiliar que acarrea los límites permitidos para el nodo actual
int bstree_validar_aux(BSTree arbol, void *minimo, void *maximo, FuncionComparadora cmp) {
  // Caso base: un árbol vacío siempre es un ABB válido
  if (arbol == NULL) return 1;

  // 1. Validar contra el límite mínimo (si existe)
  // El dato actual NO puede ser menor o igual al mínimo permitido
  if (minimo != NULL && cmp(arbol->dato, minimo) <= 0) {
    return 0; 
  }

  // 2. Validar contra el límite máximo (si existe)
  // El dato actual NO puede ser mayor o igual al máximo permitido
  if (maximo != NULL && cmp(arbol->dato, maximo) >= 0) {
    return 0;
  }

  // 3. Validar recursivamente ambos subárboles con sus rangos actualizados
  // - Para ir a la izquierda: el nuevo MAXIMO es la raíz actual.
  // - Para ir a la derecha: el nuevo MINIMO es la raíz actual.
  return bstree_validar_aux(arbol->izq, minimo, arbol->dato, cmp) &&
         bstree_validar_aux(arbol->der, arbol->dato, maximo, cmp);
}

// Función principal que llama el usuario
int bstree_validar(BSTree arbol, FuncionComparadora cmp) {
  // Inicialmente, la raíz no tiene restricciones de mínimo ni de máximo (pasamos NULL)
  return bstree_validar_aux(arbol, NULL, NULL, cmp);
}