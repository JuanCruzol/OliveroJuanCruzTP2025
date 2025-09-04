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

DNodo* crear_nodo();

DList* crear_list();

int Dlist_vacia(DList* list);

void dlist_agregar_primero(DList** list,void* dato,FuncionCopia copy);

void dlist_agregar_ultimo(DList** list,void* dato,FuncionCopia copy);

void dnodo_recorrer(DList* list,FuncionVisitante f);

void destruir_Dnodo_Dlist(DList* list,FuncionDestructora destruc);

DList* copia_dlist(DList*list);

#endif
