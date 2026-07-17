#ifndef __GLIST_H__
#define __GLIST_H__

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*Predicado)(void *dato);
typedef int (*FuncionComparadora)(void* dato1, void* dato2);
typedef struct _GNode {
  void *data;
  struct _GNode *next;
} GNode;

typedef GNode *GList;

/**
 * Devuelve una lista vacía.
 */
GList glist_crear();

/**
 * Destruccion de la lista.
 */
void glist_destruir(GList lista, FuncionDestructora destruir);

/**
 * Determina si la lista es vacía.
 */
int glist_vacia(GList lista);

/**
 * Agrega un elemento al inicio de la lista.
 */
GList glist_agregar_inicio(GList lista, void *dato, FuncionCopia copiar);

/**
 * Agrega un elemento al final de la lista.
 */
GList glist_agregar_final(GList lista, void *dato, FuncionCopia copiar);


/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList lista, FuncionVisitante visitar);


GList glist_filtrar(GList lista, FuncionCopia c, Predicado p);


/*
  Retorna 1 si el dato está en la lista, 0 si no.
*/
int glist_contiene(GList lista, void* dato, FuncionComparadora cmp);


/*
  Retorna el elemento si está en la lista, NULL si no
*/
GList glist_buscar(GList lista, void* dato, FuncionComparadora cmp);

#endif /* __GLIST_H__ */
