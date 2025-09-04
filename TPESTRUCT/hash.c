#include"hash.h"

char *mi_strdup(char *origal){
    char *copia = malloc(sizeof(char)*(strlen(origal) + 1));    
    strcpy(copia, origal);
    return copia;
}

TablaHash* inicializarHash(unsigned int size){
    TablaHash *tabla = malloc(sizeof(TablaHash));
    tabla->casillas = malloc(sizeof(Hashcasillas)*size);
    for (unsigned int i = 0; i < size; i++){
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
    unsigned int nuevoSize = (*tabla)->size * 2 + 1; // tamaño nuevo
    TablaHash *nueva = inicializarHash(nuevoSize);
    unsigned int size=(*tabla)->size;
    for (unsigned int i = 0; i < size; i++) {
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
    
    double FactorCarga = (double)((*tabla)->casillasOcupadas + 1)/(*tabla)->size;
    if (FactorCarga > FACTORCARGA){
        rehash((tabla));
    }
    int flag=1;
    unsigned int indice=hasheo(nombre) % (*tabla)->size;
    while((*tabla)->casillas[indice].ocupado && flag){
        if(strcmp((*tabla)->casillas[indice].nombre, nombre)==0){
            flag=0;
        }
        else{ 
            indice=(indice + 1)%((*tabla)->size);
        }
    }
    (*tabla)->casillas[indice].nombre=mi_strdup(nombre);
    if(definicion==NULL){
        (*tabla)->casillas[indice].definicion=NULL;
    }
    else{
        (*tabla)->casillas[indice].definicion=mi_strdup(definicion);
    }
    (*tabla)->casillas[indice].ocupado=1;
    (*tabla)->casillasOcupadas++;
}

char* buscar(TablaHash *tabla, char *nombre) {
    unsigned int indice=hasheo(nombre) % tabla->size;
    unsigned int inicio=indice; 
    int bandera=1;
    char* resultado=NULL; 
    while(tabla->casillas[indice].ocupado && bandera){
        if(strcmp(tabla->casillas[indice].nombre,nombre)==0){
            //lo guardamos
            resultado=tabla->casillas[indice].definicion; 
            //SAlimos porq lo encontramos
            bandera = 0;  
        } 
        else{
            indice=(indice+1)%tabla->size; 
            if (indice==inicio) {
                //salimos porq ya vimos que no esta
                bandera=0;  
            }
        }
    }
    return resultado; 
}
void liberarHash(TablaHash *tabla){
    unsigned int size=tabla->size;
    for (unsigned int i=0; i<size;i++){
        if (tabla->casillas[i].ocupado){
            free(tabla->casillas[i].nombre);
            if(tabla->casillas[i].definicion!=NULL){
                free(tabla->casillas[i].definicion);
            }
        }
    }
    free(tabla->casillas);
    free(tabla);
}

