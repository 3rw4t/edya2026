#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

static void imprimir_entero(int data) {
  printf("%d ", data);
}

int main() {
  BTree ll = btree_unir(1, btree_crear(), btree_crear());
  BTree l = btree_unir(2, ll, btree_crear());
  BTree r = btree_unir(3, btree_crear(), btree_crear());
  BTree raiz = btree_unir(4, l, r);
  BTree raizCopia = btree_copiar(raiz);
  btree_recorrer(raiz, BTREE_RECORRIDO_PRE, imprimir_entero);
  puts("");
  printf("\ncantidad de nodos: %d\n", btree_nnodos(raiz));
  printf("\n1 está?: %d\n", btree_buscar(raiz, 1));
  printf("\n99 está?: %d\n", btree_buscar(raiz, 99));
  btree_destruir(raiz);

  btree_recorrer(raizCopia, BTREE_RECORRIDO_PRE, imprimir_entero);
  puts("");
  printf("\nraizCopia cantidad de nodos: %d\n", btree_nnodos(raizCopia));
  printf("\nraizCopia 1 está?: %d\n", btree_buscar(raizCopia, 1));
  printf("\nraizCopia 99 está?: %d\n", btree_buscar(raizCopia, 99));
  printf("\nraizCopia altura: %d\n", btree_altura(raizCopia));
  
  btree_destruir(raizCopia);

  return 0;
}
