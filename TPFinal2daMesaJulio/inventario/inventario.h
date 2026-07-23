#include "../tablahash/tablahash.h"
#include "../avl/avl.h"

#ifndef __INVENTARIO_H__
#define __INVENTARIO_H__

typedef struct _Item{
    int id;
    char* nombre;
    double precio;
    int stock;
}* Item;

typedef struct _Inventario{
    TablaHash tabla;
    AVL avl;
} *Inventario;



Inventario inventario_crear(int capacidad);

Item item_crear(int id, char* nombre, double precio, int stock);

void item_imprimir(Item it);

Item item_copiar(Item it);

void item_destruir(Item it);

void item_destruir_avl(Item it);

int item_comparar_id(Item i1, Item i2);

int item_comparar_precio(Item i1, Item i2);

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
    Reduce en 'porcentaje' el precio del producto con el id dado. Si no existe un producto con ese id, la función no tiene efecto.
*/
void inventario_aplicar_descuento(Inventario inv, double precio_min, double precio_max, double porcentaje);

#endif