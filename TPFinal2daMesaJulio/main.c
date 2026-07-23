#include "inventario/inventario.h"
#include <stdio.h>
#include <stdlib.h>

#define CAPACIDAD_INICIAL 11
#define MAX_NOMBRE 100
int main() {
    Inventario inv = inventario_crear(CAPACIDAD_INICIAL);

    printf("carga de inventario\n");
    inventario_insertar(inv, 1, "Papas", 3000.0, 15);
    inventario_insertar(inv, 13, "Mani", 2550.0, 10);
    inventario_insertar(inv, 56, "Huevos", 3000.0, 5);
    inventario_insertar(inv, 5, "Huevos2", 3000.0, 5);
    inventario_insertar(inv, 12, "Monitor", 280000.0, 2);

    printf("\n[Estado Inicial - Listado por rango del AVL ($0 a $300,000)]:\n");
    // Nota: Deberían salir ordenados por PRECIO de menor a mayor (Mani -> Papas -> Huevos -> Monitor)
    inventario_listar_rango(inv, 0.0, 300000.0);

    // ---------------------------------------------------------
    printf("\n=== 2. PRUEBA DE ACTUALIZACIÓN DE STOCK ===\n");
    printf("-> Actualizando stock del ID 1 (Papas) de 15 a 100...\n");
    inventario_actualizar_stock(inv, 1, 100);

    printf("\nVerificando lectura desde la Tabla Hash (inventario_buscar_por_id):\n");
    Item p1 = inventario_buscar_por_id(inv, 1);
    if (p1) {
        printf("\tHash devolvió -> ");
        item_imprimir(p1);
    }

    printf("\nVerificando sincronización desde el AVL (inventario_listar_rango):\n");
    // Al listar el rango, "Papas" DEBE aparecer con Stock 100.
    inventario_listar_rango(inv, 2900.0, 3100.0);

    // ---------------------------------------------------------
    printf("\n=== 3. PRUEBA CRÍTICA: ACTUALIZACIÓN DE PRECIO ===\n");
    printf("-> Actualizando precio del ID 2 (Mani) de $2550.0 a $4000.0...\n");
    // Al subir a $4000, "Mani" pasa a ser más caro que "Papas" ($3000) y "Huevos" ($3500).
    inventario_actualizar_precio(inv, 2, 4000.0);

    printf("\nVerificando lectura desde la Tabla Hash:\n");
    Item p2 = inventario_buscar_por_id(inv, 2);
    if (p2) {
        printf("\tHash devolvió -> ");
        item_imprimir(p2);
    }

    printf("\nVerificando REORDENAMIENTO en el AVL (Listado completo):\n");
    // Si la lógica de "sacar -> modificar -> reinsertar" funcionó,
    // "Mani" ahora tiene que imprimirse DESPUÉS de "Huevos".
    inventario_listar_rango(inv, 0.0, 300000.0);

    // ---------------------------------------------------------
    printf("\n=== 4. PRUEBA DE ROBUSTEZ (IDs INEXISTENTES) ===\n");
    printf("-> Intentando actualizar stock y precio del ID 99 (no existe)...\n");
    inventario_actualizar_stock(inv, 99, 500);
    inventario_actualizar_precio(inv, 99, 9999.0);
    printf("¡Excelente! El programa ignoró el ID 99 y no crasheó.\n");

    printf("\n=== PRUEBA FINALIZADA CON ÉXITO ===\n");
    
    // Acá iría inventario_destruir(inv) en el futuro

    // ---------------------------------------------------------
    printf("\n=== 5. PRUEBA DE DESCUENTO POR RANGO ===\n");
    printf("-> Aplicando 50%% de descuento a productos entre $3000 y $5000...\n");
    // Esto debería afectar a: Papas ($3000), Huevos ($3500) y Mani ($4000).
    // El Monitor ($280000) no debería sufrir cambios.
    inventario_aplicar_descuento(inv, 3000.0, 5000.0, 50.0);

    printf("\nVerificando REORDENAMIENTO y NUEVOS PRECIOS en el AVL:\n");
    // Orden esperado de menor a mayor precio ahora:
    // 1. Papas ($1500)
    // 2. Huevos ($1750)
    // 3. Mani ($2000)
    // 4. Monitor ($280000)
    inventario_listar_rango(inv, 0.0, 300000.0);

    printf("\nVerificando que la Tabla Hash también vea los precios con descuento:\n");
    Item p_huevo = inventario_buscar_por_id(inv, 56);
    if (p_huevo) {
        printf("\tHash devolvió Huevos -> ");
        item_imprimir(p_huevo);
    }
    return 0;
}