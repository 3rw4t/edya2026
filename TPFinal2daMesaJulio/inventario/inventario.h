#include "../tablahash/tablahash.h"
#include "../avl/avl.h"
#include "../glist/glist.h"
#ifndef __INVENTARIO_H__
#define __INVENTARIO_H__


/*
    Estructura del inventario.
    ¿Por qué tablahash y avl? 

    Ambas estructuras se complementan muy bien para los requisitos del tp: Por un lado se necesita encontrar rápidamente un producto para trabajar con él,
    esto de inmediato suena a tablahash por su búsqueda en O(1). Para este caso en particular, decidí manejar las colisiones con encadenamiento de listas simples

    Por otro lado, para las tareas de buscar por rangos de precios, lo primero que recordé fue un árbol binario ordenado por la facilidad para buscar valores
    mayores o menores a uno determinado, simplemente mirando a izquierda o derecha de su respectivo nodo.
    Sin saber qué valores de precios se ingresarán, es necesario asegurarse de que el árbol creado esté lo más equilibrado posible, para no perder las ventajas
    que la estructura nos ofrece. Para esto, no hay mejor opción que un AVL.

    
*/
typedef struct _Inventario *Inventario;

/*
    Estructura de item
*/
typedef struct _Item* Item;



/*
    Devuelve un inventario vacio
*/
Inventario inventario_crear(int capacidad);

/*
    Devuelve un item nuevo con los valores ingresados
*/
Item item_crear(int id, char* nombre, double precio, int stock);


/*
    Imprime los valores de un item: "ID: %d, Nombre: %s, Precio: %f, Stock: %d\n"
*/
void item_imprimir(Item it);

/*
    Devuelve una copia del item
*/
Item item_copiar(Item it);


/*
    Libera la memoria ocupada por elitem
*/
void item_destruir(Item it);

/*
    Funcion que pide la implementación de AVL para destruir el item. Debido a que la eliminacion en hash y avl a la vez conllevaría errores,
    esta función no hace nada. (Para no hacer free a una dirección qoue ya fue liberada)
*/
void item_destruir_avl(Item it);

/*
    Devuelve la diferencia entre los ids de i1 e i2 (i1->id - i2->id)
*/
int item_comparar_id(Item i1, Item i2);

/*
    Devuelve 1 si el precio de i1 es mayor a i2, -1 si es menor;
    Si tienen el mismo precio, también se comparan los ids, esto es para resolver el problema de tener distintos productos con el mismo precio
    dentro del AVL. Se tiene un criterio secundario de orden para desempatar.
    Solo devuelve 0 si tanto precio como id son iguales (lo que no tendría mucho sentido porque se estaría intentando ingresar el mismo producto 2 veces)
*/
int item_comparar_precio(Item i1, Item i2);

/*
    Función hash para los items. Simplemente devuelve el id en este caso
*/
unsigned int item_hash(Item it);

/*
    Agrega un nuevo producto al inventario.
*/
void inventario_insertar(Inventario inv, int id, char *nobre, double precio, int stock);

/*
    Devuelve el producto con el id dado, NULL si no existe.
*/
Item inventario_buscar_por_id(Inventario inv, int id);

/*
    Actualiza el stock del producto con el id dado. Si no existe, no hace nada.
*/
void inventario_actualizar_stock(Inventario inv, int id, int nuevo_stock);

/*
    Imprime los produuctos cuyo precio se encuentre en rango [precio_min, precio_max]
*/
void inventario_listar_rango(Inventario inv, double precio_min, double precio_max);

/*
    Elimina el producto con el id dado. Si no existe, no hace nada.
*/
void inventario_eliminar_por_id(Inventario inv, int id);

/*
    Actualiza el precio del producto con el id dado. Si no  existe un producto con ese id, la función no tiene efecto.
*/
void inventario_actualizar_precio(Inventario inv, int id, double nuevo_precio);

/*
    Aplica el porcentaje de descuento a los productos en el rango [precio_min, precio_max].
*/
void inventario_aplicar_descuento(Inventario inv, double precio_min, double precio_max, double porcentaje);

#endif