#include "inventario/inventario.h"
#include <stdio.h>
#include <stdlib.h>

#define CAPACIDAD 10
#define MAX_NOMBRE 100
int main(int argc, char *argv[]) {

    //chequeo si se ingresa el archivo a leer
    if (argc < 2) {
        printf("Ingrese el nombre del archivo a leer. Uso: %s [inventario.txt]\n", argv[0]);
        return 1;
    }
    
    FILE *archivo = fopen(argv[1], "r");

    //Creacion del inventario
    Inventario inv = inventario_crear(CAPACIDAD);

    //variables temporales
    int id, stock;
    double precio;
    char nombre[MAX_NOMBRE];
    int cantidad_cargados; 

    //cargando items

    puts("  2) función inventario_insertar");
    while (fscanf(archivo, "%d %99s %lf %d", &id, nombre, &precio, &stock) == 4) {
        inventario_insertar(inv, id, nombre, precio, stock);
        cantidad_cargados++;
        printf ("Insertando item °%d. ID: %d, Nombre: %s, Precio: %f, Stock: %d\n", cantidad_cargados, id, nombre, precio, stock);
        
    }
    fclose(archivo);

    puts("");
    puts("  3) Funcion inventario_buscar_por_id");

    puts("buscamos un item existente por id y lo imprimimos");
    item_imprimir(inventario_buscar_por_id(inv, 1));

    puts("Ahora intentamos imprimir un item que no existe");
    item_imprimir(inventario_buscar_por_id(inv, 57));

    puts("");
    puts("  4) Funcion inventario_actualizar_stock");
    puts("Aumentamos el stock del jabón(id: 1) de 15 a 30");
    inventario_actualizar_stock(inv, 1, 30);
    item_imprimir(inventario_buscar_por_id(inv, 1));

    puts("");

    puts("  5) Función inventario_listar_rango");
    puts("listamos los productos entre 2000 y 10000");
    inventario_listar_rango(inv, 2000.0, 10000.0);

    puts("");

    puts("  6) Función inventario_eliminar_por_id");
    puts("aprovechamos a eliminar la carneVencida (id: 81), ya que podría perjudicar nuestra reputación.");
    inventario_eliminar_por_id(inv, 81);
    puts("Listamos otra vez los productos cuyo precio esté en el rango [2000, 10000]");
    inventario_listar_rango(inv, 2000.0, 10000.0);

    puts("");
    
    puts("  7) Función inventario_actualizar_precio");
    puts("Ya que disminuye la oferta de carne(id: 34), podemos aumentar un poco el precio");
    inventario_actualizar_precio(inv, 34, 9999.999);
    puts("Listamos una vez más los productos cuyo precio esté en el rango [2000, 10000]");
    inventario_listar_rango(inv, 2000.0, 10000.0);
    
    puts("");
    puts(" 8) Función inventario_aplicar_descuento");
    puts("Aplicamos un despuento del 33%% a todos los productos en el rango [2000, 10000]");
    inventario_aplicar_descuento(inv, 2000, 10000, 33);
    puts("Finalmente, vemos los productos cuyo precio esté en el rango [2000, 10000]");
    inventario_listar_rango(inv, 2000.0, 10000.0);
    
    return 0;
}