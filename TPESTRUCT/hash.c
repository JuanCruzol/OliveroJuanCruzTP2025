#include"hash.h"

char *mi_strdup(char *origal){
    char *copia = malloc(sizeof(char)*(strlen(origal) + 1));    
    strcpy(copia, origal);
    return copia;
}

TablaHash* inicializarHash(size_t size) {
    TablaHash *tabla = malloc(sizeof(TablaHash));
    tabla->casillas = malloc(sizeof(Hashcasillas)*size);
    for (size_t i = 0; i < size; i++){
        tabla->casillas[i].ocupado=0;
        tabla->casillas[i].nombre=NULL;
        tabla->casillas[i].definicion=NULL;
    }
    tabla->size = size;
    tabla->casillasOcupadas = 0;
    return tabla;
}

unsigned long hasheo(const char *str){
    unsigned long hash = 5381;
    int c;
    
    while ((c = *(str++))){
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

void rehash(TablaHash **tabla) {
    size_t nuevoSize = (*tabla)->size * 2 + 1; // tamaño nuevo
    TablaHash *nueva = inicializarHash(nuevoSize);
    size_t size=(*tabla)->size;
    for (size_t i = 0; i < size; i++) {
        if ((*tabla)->casillas[i].ocupado) {
            insertar(&nueva, (*tabla)->casillas[i].nombre, (*tabla)->casillas[i].definicion);
            free((*tabla)->casillas[i].nombre);
            free((*tabla)->casillas[i].definicion);
        }
    }

    free((*tabla)->casillas);
    free(*tabla);
    *tabla = nueva;
}

void insertar(TablaHash **tabla,char *nombre,char *definicion){
    
    double FactorCarga = (double) ((*tabla)->casillasOcupadas + 1) / (*tabla)->size;
    if (FactorCarga > FACTORCARGA) {
        rehash((tabla));
    }

    size_t indice = hasheo(nombre) % (*tabla)->size;
    while ((*tabla)->casillas[indice].ocupado) {
        if (strcmp((*tabla)->casillas[indice].nombre, nombre) == 0) {
            return;
        }
        indice = (indice + 1) % ((*tabla)->size);
    }
    (*tabla)->casillas[indice].nombre = mi_strdup(nombre);
    (*tabla)->casillas[indice].definicion = mi_strdup(definicion);
    (*tabla)->casillas[indice].ocupado = 1;
    (*tabla)->casillasOcupadas++;
    return;
}

char* buscar(TablaHash *tabla,char *nombre){
    size_t indice = hasheo(nombre) % tabla->size;
    size_t inicio = indice; 
    int bandera=1;
    while (tabla->casillas[indice].ocupado && bandera) {
        if (strcmp(tabla->casillas[indice].nombre, nombre) == 0) {
            return tabla->casillas[indice].definicion; // LISTO
        }
        indice = (indice + 1) % tabla->size; 
        if (indice == inicio){
            bandera=0;
        } 
    }
    return NULL; 
}

void liberarHash(TablaHash *tabla) {
    size_t size=tabla->size;
    for (size_t i = 0; i < size; i++) {
        if (tabla->casillas[i].ocupado) {
            free(tabla->casillas[i].nombre);
            free(tabla->casillas[i].definicion);
        }
    }
    free(tabla->casillas);
    free(tabla);
}
