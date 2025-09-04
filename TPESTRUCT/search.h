#ifndef __SEARCH_H__
#define __SEARCH_H__

#include"cola.h"
#include"dlist.h"
#include"apply.h"
#include"hash.h"

typedef struct estado_{
    int size;
    int cant_max;//esto para las listas de lista
    DList** lista_de_lista;
    char* cadena_formada;//donde guardamos la funcion
} Estado;

typedef struct _arreglo_dlist{
    int cant_max;
    int size;
    DList** lista_de_lista;
    
}Arreglo_Dlist;

/*
Esta funcion q encarga de verificar que el coanndo de search este
escrito de manera correcta osea que luego del search haya algo de la forma
{L11,L12; ....;Ln1,Ln2};
*/
//int verificar_search(char* comando, TablaHash* tabla_de_listas,Estado** estado,Arreglo_Dlist** l_de_l);

/*
FUNCION ENCARGADA DE CREAR UN ESTADO
*/
Estado* crear_estado();

/*
funcion q destruye estado
*/
void destruir_estado(Estado* estado);

/*
Funcion q dado una lista representada de la forma [] o por defl agrega la lista al estado
*/
Estado* agregar_lista_a_estado(Estado* estado,char lista_a_agregar[],TablaHash* tabla_de_listas);

/*
Funcion q hace una copia fisica del esatdo
*/
Estado* copiar_estado(Estado* estado);

/*
Funcion q dado una funcion primitiva, o en la tabla de funciones, aplica esa funcion a todas las lisats guardadas
y tambien concatena en esatdo la funcion q se aplico
*/
Estado* aplicar_funcion_a_estado(Estado* actual_esatado, char* funcion_a_aplicar, TablaHash* tabla_de_funciones);

/*
Funcion q inicializa una estructua Arreglo_Dlist
*/
Arreglo_Dlist* inicializar_lista_de_lista();

/*
destruye la estructura
*/
void destruir_lista_de_lista(Arreglo_Dlist* l_d_l);

/*
Funcion q dado un array de char osea string, de la forma [] o definido con defl agrega la lista al arreglo_dlist
*/
Arreglo_Dlist* agregar_a_lista_de_listas(Arreglo_Dlist* l_de_l,TablaHash* tabla_de_listas,char lista_a_agregar[]);


/*
Dadas 2 dlist retorna 1 si son iguales, 0 en caso contrario
*/
int listas_iguales(DList* lista1,DList* lista2);

/*
Funcion q dadas 2 arrays de lisats retorna 1 si ambos array son iguales, caso contrario 0
*/
int lista_de_listas_iguales(DList** lista_de_lista1,DList** lista_de_lista2,int size);

/*
Funcion q buscara llgar de estado_init a l_de_l si lo logro dice q funciones uso
*/
void buscar_solucion(Estado* estado_init,Arreglo_Dlist* l_de_l,TablaHash* tabla_de_funciones);

/*
Funcion q se encarga de realizar el search, para eso verificamos que sea valida y mientras validamos guardamos
*/
void funcion_search(char* comando, TablaHash* tabla_de_listas,TablaHash* tabla_de_funciones);

#endif