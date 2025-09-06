#ifndef __APPLY_H__
#define __APPLY_H__


#include"defl.h"

/*
Verifica q la expresion de apply sea valida, 
pos_lista se utiliza para ya saber la posicion de la lista asi no corrermos otra vez para saber donde esta

*/
int isValidApply(char* definicion, TablaHash* tabla_de_funciones,TablaHash* tabla_de_listas,int * pos_lista);

/*
Funcion q dad una lista dada de la forma [...] o con nombre, con su tabla de listas, la trasforma a una Dlist
*/
DList* pasar_a_lista(char* expresion_lista,TablaHash* tabla_de_listas);

/*
Funcion que dado un comando y una lista aplica la funcion del comando sobre la lista
los posibles comando son 0i 0d Dd Di, etc osea son las primitivas
*/
DList* aplicar_primitiva(char* comando,DList* lista);


/*
Funcion que se utiliza cuando se tiene un comando de la forma < f >
se encarga de aplicar f (llamando a aplicar_funcion_a_lista) hasta q sus extremos sean iguales
el comando q hay de argumento es el f que esta entre <>, no se tiene estos
*/
DList* aplicar_repeticion(DList* lista,char *comando,TablaHash* tabla_de_funciones);


/*
Dada una lista, una funcion F y la tabla de funciones, esta funcon se encarga de aplicar
f sobre la lista, f se toma como valida pues ya se reviso
*/
DList* aplicar_funcion_a_lista(DList* lista, char* funcion,TablaHash* tabla_de_funciones);

/*
Funcion q se encarga de imprimir por pantalla la lista, pero de la forma [ dato,dato,dato,....]
*/
void imprimir_Lista(DList* lista);

/*
funcion q cuando se utiliza cuando el usuario escribe apply
*/
void funcion_apply(char* definicion, TablaHash* tabla_de_funciones,TablaHash* tabal_de_listas);


#endif