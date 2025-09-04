#ifndef __SEARCH3_H__
#define __SEARCH3_H__

#include"apply.h"
#include"cola.h"

typedef struct estado_{
    int size;
    int cant_max;//esto para los reallocs
    DList** lista_de_lista;
    char* cadena_formada;
} Estado;

typedef struct _arreglo_dlist{
    int cant_max;
    int size;
    DList** lista_de_lista;
    
}Arreglo_Dlist;

/*
Funcion q se encarga de inicialzar una estructura de tipo estado
*/
Estado* inicializar_esatdo();

/*
Funcion q dado un string q representa un lista de la forma [] o ya definida con el defl
la pasa a Dlist para luego guardarla en la estrucrua estado
*/
Estado* agregar_lista_a_estado(Estado* estado,char lista_a_agregar[],TablaHash* tabla_de_listas);

/*
Funcion q inicializa una estructua Arreglo_Dlist
*/
Arreglo_Dlist* inicializar_lista_de_lista();

/*
Fncion q dado un string q represneta a una lista defina por el defl o de la forma []
se encarga de pasar esa lista a Dlist para luego agregarla a la estrucrura
*/
Arreglo_Dlist* agregar_a_lista_de_listas(Arreglo_Dlist* l_de_l,TablaHash* tabla_de_listas,char lista_a_agregar[]);

/*
Funcion q libera una estructura de tipo esatdo
*/
void destruir_estado(Estado* estado);

/*
funcion q libera una estrutura arreglo_dlist
*/
void destruir_lista_de_lista(Arreglo_Dlist* l_de_l);

/*
Esta funcion q encarga de verificar que el coanndo de search este
escrito de manera correcta osea que luego del search haya algo de la forma
{L11,L12; ....;Ln1,Ln2};
*/
int verificar_search(char* comando, TablaHash* tabla_de_listas,Estado** estado,Arreglo_Dlist** l_de_l);

/*
Funcion q se encarga de realizar el search, para eso verificamos que sea valida y mientras validamos guardamos
*/
void funcion_search(char* comando, TablaHash* tabla_de_listas,TablaHash* tabla_de_funciones);


#endif