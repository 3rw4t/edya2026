#include "inventario.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


struct _Inventario{
    TablaHash tabla;
    AVL avl;
};

struct _Item{
    int id;
    char* nombre;
    double precio;
    int stock;
};

/*
    Estructura auxiliar para aplicar un determinado descuento a los productos dentro del rango requerido
*/
typedef struct {
    double min;
    double max;
    GList productos;
} ContextoRango;


/*
    Devuelve un inventario vacio
*/
Inventario inventario_crear(int capacidad){
    Inventario inv = malloc(sizeof(struct _Inventario));
    assert(inv != NULL);

    inv->tabla = tablahash_crear(capacidad, (FuncionCopiadora) item_copiar, (FuncionComparadora) item_comparar_id,(FuncionDestructora) item_destruir, (FuncionHash) item_hash);
    assert(inv->tabla != NULL);

    inv->avl = avl_crear((FuncionCopiadora) item_copiar, (FuncionComparadora) item_comparar_precio, (FuncionDestructora) item_destruir_avl);
    assert(inv->avl != NULL);

    return inv;
}

/*
    Devuelve un item nuevo con los valores ingresados
*/
Item item_crear(int id, char* nombre, double precio, int stock){
    assert(nombre != NULL);
    assert(precio >= 0);
    assert(stock >= 0);

    Item it = malloc(sizeof(struct _Item));
    assert(it);

    it->id = id;
    it->nombre = malloc(sizeof(char) * (strlen(nombre) + 1));
    assert(it->nombre);

    strcpy(it->nombre, nombre);
    it->precio = precio;
    it->stock = stock;

    return it;
}

/*
    Imprime los valores de un item: "ID: %d, Nombre: %s, Precio: %f, Stock: %d\n"
*/
void item_imprimir(Item it){
    if(it){
        printf("ID: %d, Nombre: %s, Precio: %f, Stock: %d\n", it->id, it->nombre, it->precio, it->stock);
    }else{
        printf("El item no existe!\n");  
    }
     
}

/*
    Devuelve una copia del item
*/
Item item_copiar(Item it){
    return it;
}

/*
    Libera la memoria ocupada por elitem
*/
void item_destruir(Item it){
    assert(it != NULL);
    assert(it->nombre != NULL);

    free(it->nombre);
    free(it);
}

/*
    Funcion que pide la implementación de AVL para destruir el item. Debido a que la eliminacion en hash y avl a la vez conllevaría errores,
    esta función no hace nada. (Para no hacer free a una dirección qoue ya fue liberada)
*/
void item_destruir_avl(Item it){
    if(it) return;
}

/*
    Devuelve la diferencia entre los ids de i1 e i2 (i1->id - i2->id)
*/
int item_comparar_id(Item i1, Item i2){
    assert(i1 != NULL);
    assert(i2 != NULL);
  
    return i1->id - i2->id;
}

/*
    Devuelve 1 si el precio de i1 es mayor a i2, -1 si es menor;
    Si tienen el mismo precio, también se comparan los ids, esto es para resolver el problema de tener distintos productos con el mismo precio
    dentro del AVL. Se tiene un criterio secundario de orden para desempatar.
    Solo devuelve 0 si tanto precio como id son iguales (lo que no tendría mucho sentido porque se estaría intentando ingresar el mismo producto 2 veces)
*/
int item_comparar_precio(Item i1, Item i2){
    assert(i1 != NULL);
    assert(i2 != NULL);

    if (i1->precio < i2->precio) return -1;
    if (i1->precio > i2->precio) return 1;
    if (i1->id < i2->id) return -1;
    if (i1->id > i2->id) return 1;
    return 0;
}

/*
    Función hash para los items. Simplemente devuelve el id en este caso
*/
unsigned int item_hash(Item it){
    assert(it != NULL);

    return (unsigned int)it->id;
}

/*
    Agrega un nuevo producto al inventario.
*/
void inventario_insertar(Inventario inv, int id, char *nombre, double precio, int stock){
    assert(inv != NULL);
    assert(inv->tabla != NULL);

    struct _Item temp = {.id = id, .nombre = NULL, .precio = 0.0, .stock = 0};
    if(tablahash_buscar(inv->tabla, &temp) != NULL) return;

    Item nuevo = item_crear(id, nombre, precio, stock);
    tablahash_insertar(inv->tabla, nuevo);
    avl_insertar(inv->avl, nuevo);
}

/*
    Devuelve el producto con el id dado, NULL si no existe.
*/
Item inventario_buscar_por_id(Inventario inv, int id){
    assert(inv != NULL);
    assert(inv->tabla != NULL);

    struct _Item temp = {.id =id, .nombre = NULL, .precio=0, .stock=0};

    Item resultado = tablahash_buscar(inv->tabla, &temp);
    return resultado ;
}

/*
    Actualiza el stock del producto con el id dado. Si no existe, no hace nada.
*/
void inventario_actualizar_stock(Inventario inv, int id, int nuevo_stock){
    assert(inv != NULL);
    assert(inv->tabla != NULL);

    struct _Item temp = {.id =id, .nombre = NULL, .precio=0, .stock=0};
    Item resultado = tablahash_buscar(inv->tabla, &temp);
    if(resultado)resultado->stock = nuevo_stock;
}

/*
    Funcion auxiliar para inventario_listar_rango. La idea es aprovechar la función avl_recorrer
*/
void imprimir_si_en_rango(void* dato, void* extra) {
    Item it = (Item)dato;
    ContextoRango* rango = (ContextoRango*)extra;

    if (it->precio >= rango->min && it->precio <= rango->max) item_imprimir(it);
}

/*
    Imprime los productos cuyo precio se encuentre en rango [precio_min, precio_max]
*/
void inventario_listar_rango(Inventario inv, double precio_min, double precio_max) {
    assert(inv != NULL);
    assert(inv->avl != NULL);
    assert(precio_min <= precio_max);
    
    ContextoRango rango = {.min = precio_min, .max = precio_max, .productos = NULL};

    avl_recorrer(inv->avl, AVL_RECORRIDO_IN, imprimir_si_en_rango, &rango);
}

/*
    Elimina el producto con el id dado. Si no existe, no hace nada.
*/
void inventario_eliminar_por_id(Inventario inv, int id){
    assert(inv != NULL);
    assert(inv->tabla != NULL);

    struct _Item temp = {.id = id, .nombre = NULL, .precio = 0.0, .stock = 0};

    Item eliminar = tablahash_buscar(inv->tabla, &temp);

    if (!eliminar) return;
    avl_eliminar(inv->avl, eliminar);
    tablahash_eliminar(inv->tabla, eliminar);
}

/*
    Actualiza el precio del producto con el id dado. Si no  existe un producto con ese id, la función no tiene efecto.
*/
void inventario_actualizar_precio(Inventario inv, int id, double nuevo_precio){
    assert(inv != NULL);
    assert(inv->tabla != NULL);

    Item it = inventario_buscar_por_id(inv,id);
    
    if (!it) return;

    avl_eliminar(inv->avl, it);
    it->precio = nuevo_precio;
    avl_insertar(inv->avl, it);
}


/*
    Función visitante que compara el precio del item y si lo agrega a la lista si es necesario
*/
void recolectar_para_descuento(void* dato, void* extra) {
    Item prod = (Item)dato;
    assert(extra != NULL);
    ContextoRango* ctx = (ContextoRango*)extra;

    if (prod->precio >= ctx->min && prod->precio <= ctx->max) {

        // NULL ya que la idea es guardar el puntero temporalmente. 
        ctx->productos = glist_agregar_inicio(ctx->productos, prod, (FuncionCopia) item_copiar);
    }
}

/*
    Aplica el porcentaje de descuento a los productos en el rango [precio_min, precio_max].
*/
void inventario_aplicar_descuento(Inventario inv, double precio_min, double precio_max, double porcentaje) {
    assert(inv != NULL);
    assert(inv->avl != NULL);
    assert(precio_min <= precio_max);

    // se crean 2 items temporales como cotas
    // al minimo se le pone id 0 y al segundo un id gigante (segun google ese es el valor maximo para int)
    struct _Item lim_min = {.id = 0, .nombre = NULL, .precio = precio_min, .stock = 0};
    struct _Item lim_max = {.id = 2147483647, .nombre = NULL, .precio = precio_max, .stock = 0};

    ContextoRango ctx = {.min = precio_min, .max = precio_max, .productos = NULL};

    // se recorre una parte del AVL
    avl_recorrer_rango(inv->avl, &lim_min, &lim_max, recolectar_para_descuento, &ctx);

    GList actual = ctx.productos;
    while (actual != NULL) {
        Item prod = (Item)actual->data;

        avl_eliminar(inv->avl, prod);
        prod->precio -= prod->precio * (porcentaje / 100.0);
        avl_insertar(inv->avl, prod);

        actual = actual->next;
    }

    glist_destruir(ctx.productos, (FuncionDestructora) item_destruir_avl);
}


