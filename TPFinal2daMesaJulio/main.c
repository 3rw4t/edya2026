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
    while (fscanf(archivo, "%d %99s %lf %d", &id, nombre, &precio, &stock) == 4) {
        inventario_insertar(inv, id, nombre, precio, stock);
        cantidad_cargados++;
        printf ("Insertando item °%d. ID: %d, Nombre: %s, Precio: %f, Stock: %d\n", cantidad_cargados, id, nombre, precio, stock);
        
    }
    fclose(archivo);

    puts("");

    //buscamos un item por id
    item_imprimir(inventario_buscar_por_id(inv, 1));



    return 0;
}