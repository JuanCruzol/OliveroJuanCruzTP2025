#ifndef __COLA_H__
#define __COLA_H__

typedef struct _Gnodo{
    void* dato;
    struct _Gnodo* sig;
}Gnodo;

typedef struct Glist{
    Gnodo* primero;
    Gnodo* ultimo;
}Glist;

typedef Glist* Cola;

typedef void(*FuncioneVisitante)(void*);
typedef void*(*FuncioneCopia)(void*);
typedef int(*FuncioneComparadora)(void*,void*);
typedef void(*FuncionDestructora)(void*);

Cola crear_cola();

Cola agregar_dato_prioridad(Cola cola,void* dato,FuncioneCopia copy);

Cola cola_encolar(Cola cola,void* dato,FuncioneCopia copy);

int cola_vacia(Cola cola);

void* cola_desencolar(Cola cola);

void* cola_inicio(Cola cola);

void cola_imprimir(Cola cola, FuncioneVisitante f);

void cola_destruir(Cola cola,FuncionDestructora destroy);


#endif
