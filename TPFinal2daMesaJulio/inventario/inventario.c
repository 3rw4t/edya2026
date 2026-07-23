#include "inventario.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct {
    double min;
    double max;
} RangoPrecio;

/*
    Funcion para inciar un inventario    
*/
Inventario inventario_crear(int capacidad){
    Inventario inv = malloc(sizeof(struct _Inventario));
    inv->tabla = tablahash_crear(capacidad, (FuncionCopiadora) item_copiar, (FuncionComparadora) item_comparar_id,(FuncionDestructora) item_destruir, (FuncionHash) item_hash);
    inv->avl = avl_crear((FuncionCopiadora) item_copiar, (FuncionComparadora) item_comparar_precio, (FuncionDestructora) item_destruir_avl);
    return inv;
}


Item item_crear(int id, char* nombre, double precio, int stock){
    Item it = malloc(sizeof(struct _Item));
    it->id = id;
    it->nombre = malloc(sizeof(char) * (strlen(nombre) + 1));
    strcpy(it->nombre, nombre);
    it->precio = precio;
    it->stock = stock;

    return it;
}

/*
    Compara items por ID
*/
int item_comparar_id(Item i1, Item i2){
    return i1->id - i2->id;
}

/*
    Compara items por precio y id;
*/
int item_comparar_precio(Item i1, Item i2){
    if (i1->precio < i2->precio) return -1;
    if (i1->precio > i2->precio) return 1;
    if (i1->id < i2->id) return -1;
    if (i1->id > i2->id) return 1;
    return 0;
}

/*
    Devuelve una copia del item
*/
Item item_copiar(Item it){
    return it;
}

/*
    Destruye el item
*/
void item_destruir(Item it){
    free(it->nombre);
    free(it);
}

/*
    Funcion destructuora para el avl
*/
void item_destruir_avl(Item it){
    if(it) return;
}

/*
    funcion hash del item
*/
unsigned int item_hash(Item it){
    return (unsigned int)it->id;
}

void item_imprimir(Item it){
    printf("ID: %d, Nombre: %s, Precio: %f, Stock: %d\n", it->id, it->nombre, it->precio, it->stock);
}

/*
    Agrega un nuevo producto al inventario.
*/
void inventario_insertar(Inventario inv, int id, char *nombre, double precio, int stock){
    if(!inv) return;
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
    if(!inv) return NULL;

    struct _Item temp = {.id =id, .nombre = NULL, .precio=0, .stock=0};
    printf("\n[DEBUG] ID buscado: %d | Hash calculado: %d | Casilla: %d\n", 
           id, item_hash(&temp), item_hash(&temp) % tablahash_capacidad(inv->tabla));
    
    Item resultado = tablahash_buscar(inv->tabla, &temp);
    return resultado ;
}

/*
    Actualiza el stock del producto con el id dado. Si no existe, no hace nada.
*/
void inventario_actualizar_stock(Inventario inv, int id, int nuevo_stock){
    struct _Item temp = {.id =id, .nombre = NULL, .precio=0, .stock=0};
    Item resultado = tablahash_buscar(inv->tabla, &temp);
    if(resultado)resultado->stock = nuevo_stock;
}


void imprimir_si_en_rango(void* dato, void* extra) {
    Item prod = (Item)dato;
    RangoPrecio* rango = (RangoPrecio*)extra;

    if (prod->precio >= rango->min && prod->precio <= rango->max) printf("ID: %d, Nombre: %s, Precio: %f, Stock: %d\n", prod->id, prod->nombre, prod->precio, prod->stock);
}

/*
    Imprime los productos cuyo precio se encuentre en rango [precio_min, precio_max]
*/
void inventario_listar_rango(Inventario inv, double precio_min, double precio_max) {
    if (!inv || !inv->avl) return;

    RangoPrecio rango = { .min = precio_min, .max = precio_max };

    avl_recorrer(inv->avl, AVL_RECORRIDO_IN, imprimir_si_en_rango, &rango);
}

void inventario_eliminar_por_id(Inventario inv, int id){
    if (!inv) return;

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
    if (!inv) return;

    Item it = inventario_buscar_por_id (inv,id);
    
    if (!it) return;

    avl_eliminar(inv->avl, it);
    it->precio = nuevo_precio;
    avl_insertar(inv->avl, it);

}

// 1. Estructura para guardar el contexto del recorrido y el arreglo dinámico
typedef struct {
    double min;
    double max;
    Item *productos_a_modificar; // Arreglo de punteros a Item
    int cantidad;
    int capacidad;
} ContextoDescuento;

// 2. Función visitante: solo guarda los productos que cumplen la condición en el arreglo
static void recolectar_para_descuento(void* dato, void* extra) {
    Item prod = (Item)dato;
    ContextoDescuento* ctx = (ContextoDescuento*)extra;

    if (prod->precio >= ctx->min && prod->precio <= ctx->max) {
        // Si nos quedamos sin espacio en el arreglo temporal, pedimos más memoria
        if (ctx->cantidad == ctx->capacidad) {
            ctx->capacidad = (ctx->capacidad == 0) ? 10 : ctx->capacidad * 2;
            ctx->productos_a_modificar = realloc(ctx->productos_a_modificar, ctx->capacidad * sizeof(Item));
            assert(ctx->productos_a_modificar != NULL);
        }
        // Guardamos la referencia al producto y aumentamos el contador
        ctx->productos_a_modificar[ctx->cantidad] = prod;
        ctx->cantidad++;
    }
}

/*
    Reduce en 'porcentaje' el precio del producto con el id dado. 
    Si no existe un producto con ese id, la función no tiene efecto.
*/
void inventario_aplicar_descuento(Inventario inv, double precio_min, double precio_max, double porcentaje) {
    if (!inv || !inv->avl) return;

    // Inicializamos nuestro contexto vacío
    ContextoDescuento ctx = {
        .min = precio_min, 
        .max = precio_max, 
        .productos_a_modificar = NULL, 
        .cantidad = 0, 
        .capacidad = 0
    };

    // 1. Recolectamos los productos en el arreglo (sin modificar el árbol todavía)
    avl_recorrer(inv->avl, AVL_RECORRIDO_IN, recolectar_para_descuento, &ctx);

    // 2. Iteramos el arreglo y aplicamos la actualización segura (sacar -> mutar -> insertar)
    for (int i = 0; i < ctx.cantidad; i++) {
        Item prod = ctx.productos_a_modificar[i];

        // Lo sacamos del árbol con su precio actual (viejo)
        avl_eliminar(inv->avl, prod);

        // Calculamos y aplicamos el nuevo precio (ej: 20% descuento = precio * 0.80)
        prod->precio -= prod->precio * (porcentaje / 100.0);

        // Lo volvemos a insertar con su precio nuevo para que el AVL lo ubique bien
        avl_insertar(inv->avl, prod);
    }

    // 3. Liberamos el arreglo temporal (solo el arreglo, no los Items!)
    if (ctx.productos_a_modificar != NULL) {
        free(ctx.productos_a_modificar);
    }
}



