#ifndef __HASH_H__
#define __HASH_H__

#include<stdlib.h>
#include<string.h>
#include<stddef.h>

#define FACTORCARGA 0.75
//lo ponemos directamente como char* pues ya sabemos que va a ser de ese tipo
typedef struct {
    char *nombre;      
    char *definicion;  
    int ocupado;//0 para decir ocupado 1 para decir disponible      
} Hashcasillas;

typedef struct {
    Hashcasillas *casillas;   
    unsigned int size;          
    unsigned int casillasOcupadas;  
} TablaHash;

/*
Funcion que dado un tamano crea un tabla hash de ese tamano, inicializa todas
las casillas en NULL
*/
TablaHash* inicializarHash(unsigned int size);

/*
Como funcion HASH toma un string y sigue la funcion hash de djb2
informacion obtenida: https://stackoverflow.com/questions/7666509/hash-function-for-string
*/
unsigned long hasheo(const char *str);

/*
DEfinimos instertar que dada una tabla hash, el nombre de la funcion o lista ingresada
y lo que sigue luego del = (definicion) inserta en la tabla el nombre con la definicion
*/

void insertar(TablaHash** tabla,char* nombre, char* definicion);

/*
Como bien dice su nombre busca si el nombre se encuentra en la lista
si se encuentra retorna su valor, caso contrario retorna NULL
*/
char* buscar(TablaHash *tabla,char *nombre);

/*
Funcion que utilizaremos una vez que se cierre los comandos, liberaremos la tabla hash
*/
void liberarHash(TablaHash *tabla);

/*
Funcion que hace los mismo que strdup pero como usamos -std=c99 no se encuentra dentro de string.h
lo que hace strdup es como el strcpy donde se usa un malloc en donde se va a copiar
*/
char *mi_strdup(char *original);



#endif

