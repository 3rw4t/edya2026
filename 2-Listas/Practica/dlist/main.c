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
}

int main(){
    test_agregar_inicio();

}