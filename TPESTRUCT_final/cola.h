#ifndef __COLA_H__
#define __COLA_H__

#include"dlist.h"


typedef DList* Cola;

typedef void(*FuncioneVisitante)(void*);
typedef void*(*FuncioneCopia)(void*);
typedef int(*FuncioneComparadora)(void*,void*);
typedef void(*FuncionDestructora)(void*);

Cola crear_cola();

/*
Encolo el dato por encima de los demas, osea q tenga prioridad
*/
Cola agregar_dato_prioridad(Cola cola,void* dato,FuncioneCopia copy);

/*
funcion q agrega un dato a la cola
*/
Cola cola_encolar(Cola cola,void* dato,FuncioneCopia copy);

/*
1 si esat vacio, 0 caso contrario
*/
int cola_vacia(Cola cola);

/*
Funcion q retorna el dato de cola y destruye el nodo donde se encuentra, distonto de cola_inicio pues esa no destruye
*/
void* cola_desencolar(Cola cola);

/*
Retorna el primer dato de la cola, si esta vacio NULL
*/
void* cola_inicio(Cola cola);

/*
imprimimos los datos de la cola, dada una funcion
*/
void cola_imprimir(Cola cola, FuncioneVisitante f);

/*
liberamos la cola
*/
void cola_destruir(Cola cola,FuncionDestructora destroy);


#endif
