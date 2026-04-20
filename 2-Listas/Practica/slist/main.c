#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

static void imprimir_entero(int dato) {
  printf("%d ", dato);
}

void test_partir(){

  SList lista = slist_crear();

  lista = slist_agregar_inicio(lista, 3);
  lista = slist_agregar_inicio(lista, 2);
  lista = slist_agregar_inicio(lista, 1);
  lista = slist_agregar_final(lista, 4);
  lista = slist_agregar_final(lista, 5);
  lista = slist_agregar_final(lista, 6);
  lista = slist_agregar_final(lista, 7);
  printf("Lista sin modificar: \n");
  slist_recorrer(lista, imprimir_entero);
  puts("");

  SList listaP = slist_partir(lista);
  printf("primera parte lista partida: \n");
  slist_recorrer(lista, imprimir_entero);
  puts("");
  printf("segunda parte lista partida: \n");
  slist_recorrer(listaP, imprimir_entero);
  puts("");
  
  slist_destruir(lista);
}

void test_longitud(){

  SList lista = slist_crear();

  lista = slist_agregar_inicio(lista, 3);
  lista = slist_agregar_inicio(lista, 2);
  lista = slist_agregar_inicio(lista, 1);
  //lista = slist_agregar_final(lista, 4);
  //lista = slist_agregar_final(lista, 5);
  // lista = slist_agregar_final(lista, 6);
  // lista = slist_agregar_final(lista, 7);
  printf("Lista sin modificar: \n");
  slist_recorrer(lista, imprimir_entero);
  puts("");
  printf("Longitud de la lista: %d\n", slist_longitud(lista));
  slist_destruir(lista);
};

void test_concatenar(){
  SList lista1 = slist_crear(), lista2 = slist_crear();
  lista1 = slist_agregar_inicio(lista1, 1);
  lista1 = slist_agregar_inicio(lista1, 4);
  printf("Lista1: \n");
  slist_recorrer(lista1, imprimir_entero);
  puts("");
  
  lista2 = slist_agregar_inicio(lista2, 2);
  lista2 = slist_agregar_inicio(lista2, 7);
  printf("Lista2: \n");
  slist_recorrer(lista2, imprimir_entero);
  puts("");
  
  printf("Listas concatenadas: \n");
  slist_concatenar(lista1,lista2);
  slist_recorrer(lista1, imprimir_entero);
  puts("");

  slist_destruir(lista1);
}
void test_insertar(){

  SList lista = slist_crear();
  lista = slist_agregar_inicio(lista, 3);
  lista = slist_agregar_inicio(lista, 2);
  lista = slist_agregar_inicio(lista, 1);
  lista = slist_agregar_final(lista, 4);
  lista = slist_agregar_final(lista, 5);
  lista = slist_agregar_final(lista, 6);
  lista = slist_agregar_final(lista, 7);
  printf("Lista sin modificar: \n");
  slist_recorrer(lista, imprimir_entero);
  puts("");

  slist_insertar(lista, 0, 15);
  printf("Lista modificada: \n");
  slist_recorrer(lista, imprimir_entero);
  puts("");
}

void test_contiene(){
  SList lista = slist_crear();
  lista = slist_agregar_inicio(lista, 3);
  lista = slist_agregar_inicio(lista, 2);
  lista = slist_agregar_inicio(lista, 1);
  printf("Lista contiene 3?: %d\n", slist_contiene(lista, 3));
} 

void test_indice(){
  SList lista = slist_crear();
  lista = slist_agregar_inicio(lista, 3);
  lista = slist_agregar_inicio(lista, 2);
  lista = slist_agregar_inicio(lista, 1);
  printf("Lista contiene 1?: %d\n", slist_indice(lista, 1));
  printf("Lista contiene 2?: %d\n", slist_indice(lista, 2));
  printf("Lista contiene 3?: %d\n", slist_indice(lista, 3));
  printf("Lista contiene 5?: %d\n", slist_indice(lista, 5));
}

int main(int argc, char *argv[]) {
  //test_partir();
  //test_longitud();
  //test_concatenar();
  //test_insertar();
  //test_contiene();
  test_indice();
  return 0;
}
