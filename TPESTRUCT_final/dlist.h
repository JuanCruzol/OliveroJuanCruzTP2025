#ifndef __DLIST_H__
#define __DLIST_H__

typedef struct _DNodo {
    void* dato;
    struct _DNodo* sig;
    struct _DNodo* ant;
} DNodo;

typedef struct {
    DNodo* primero;
    DNodo* ultimo;
} DList;

typedef void(*FuncionDestructora)(void * dato);

typedef void (*FuncionVisitante)(void* dato);

typedef int (*FuncionComparadora)(void* data1,void* data2);

typedef void* (*FuncionCopia)(void* data);

/*
libera el dato
*/
void destroy(void* dato);

/*
le asigno memeria a un DNodo
*/
DNodo* crear_nodo();

/*
Creamos una dlist
*/
DList* crear_list();

/*
retorna 1 si esta vacio, 0 sino
*/
int Dlist_vacia(DList* list);

/*
agrega un dato al inicio de la lista
*/
void dlist_agregar_primero(DList** list,void* dato,FuncionCopia copy);

/*
Agrego un dato al final de la lista
*/
void dlist_agregar_ultimo(DList** list,void* dato,FuncionCopia copy);

/*
dada una funcion aplicamos esa funcion a todos los datos de la lisat
*/
void dnodo_recorrer(DList* list,FuncionVisitante f);
/*
liberamos la lista y los nodos
*/
void destruir_Dnodo_Dlist(DList* list,FuncionDestructora destruc);

/*
hacemos una copia fisica de la lista
*/
DList* copia_dlist(DList*list);

#endif
