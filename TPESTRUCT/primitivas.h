#ifndef __PRIMITIVAS_H__
#define __PRIMITIVAS_H__

#include"dlist.h"


/*
FUncion cero_izq que dada una lista, agrega un cero a la izquierda, osea en la primera posicion
*/
void cero_izq(DList** list);

/*
Funcion cero_der que dada una lista agrega un cero al final osea derecha
*/
void cero_der(DList** list);

/*
Funcion sucesor_izq, que dada una lista no vacia incrementa en uno el valor a la izquierda
osea su primer elemento, en casod e ser vacia no hace nada
*/

void sucesor_izq(DList** list);

/*
Funcion sucesor_der, que dada una lista no vacia incrementa en uno el valor a la derecha
osea el ultimo elemento, en caso de ser vacia no hace nada
*/

void sucesor_der(DList** list);

/*
Funcion borrar_izq, que dada una lista no vacia elimina el primer elemento
si esta vacia no hace nada
*/

void borrar_izq(DList** list);

/*
Funcion borrar_der, que dada una lista no vacia elimina el ultimo elemento
si esta vacia no hace nada
*/

void borrar_der(DList** list);

#endif