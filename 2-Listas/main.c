#include <stdio.h>
#include <stdlib.h>

typedef struct _SNodo {
    int dato;
    struct _SNodo * sig;
} SNodo;

void SNodo_agregar_final (SNodo ** inicio, int dato){
    if (!(*inicio)){
        (*inicio) = malloc(sizeof(SNodo));
        (*inicio)->sig = NULL;
        (*inicio)->dato = dato;
        return;
    }

    SNodo * temp = *inicio;
    for (;temp->sig; temp = temp->sig);
    temp->sig = malloc(sizeof(SNodo));
    temp->sig->sig = NULL;
    temp->sig->dato = dato;
}

void SNodo_recorrer (SNodo * inicio){
    if (!inicio){
        return;
    }
    for(;inicio;inicio = inicio->sig) {
        
        printf("%d\n",inicio->dato);
        printf("%p\n",inicio->sig);

    }
}
int main (){
    SNodo * inicio = NULL;
    SNodo_agregar_final(&inicio, 1);
    SNodo_agregar_final(&inicio, 2);
    SNodo_agregar_final(&inicio, 3);
    
    SNodo_recorrer(inicio);
    return 0;
}