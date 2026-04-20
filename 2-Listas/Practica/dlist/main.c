#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"

void test_agregar_inicio(){
    DList * lista = dlist_crear();

    lista = dlist_agregar_inicio(lista, 3);
    lista = dlist_agregar_inicio(lista, 2);
    lista = dlist_agregar_inicio(lista, 1);
    DNodo * temp = lista->primero;
    for(; temp; temp = temp->sig) printf ("dato = %d\n", temp->dato);

    dlist_destruir(lista);
    free(lista);

}

void test_agregar_final(){
    DList * lista = dlist_crear();

    lista = dlist_agregar_final(lista, 1);
    lista = dlist_agregar_final(lista, 2);
    lista = dlist_agregar_final(lista, 3);

    dlist_recorrer(lista);

    dlist_destruir(lista);
    free(lista);

}

int main(){
    //test_agregar_inicio();
    test_agregar_final();

}