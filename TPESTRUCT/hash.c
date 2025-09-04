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
    int flag=1;
    size_t indice = hasheo(nombre) % (*tabla)->size;
    while ((*tabla)->casillas[indice].ocupado && flag) {
        if (strcmp((*tabla)->casillas[indice].nombre, nombre) == 0) {
            flag=0;;
        }
        else{ 
            indice = (indice + 1) % ((*tabla)->size);
        }
    }
    (*tabla)->casillas[indice].nombre = mi_strdup(nombre);
    (*tabla)->casillas[indice].definicion = mi_strdup(definicion);
    (*tabla)->casillas[indice].ocupado = 1;
    (*tabla)->casillasOcupadas++;
    return;
}

char* buscar(TablaHash *tabla, char *nombre) {
    size_t indice = hasheo(nombre) % tabla->size;
    size_t inicio = indice; 
    int bandera = 1;
    char* resultado = NULL; 
    while (tabla->casillas[indice].ocupado && bandera) {
        if (strcmp(tabla->casillas[indice].nombre,nombre)==0){
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
    return resultado; // un solo return al final
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


HashSet* crear_hashset(int capacidad) {
    HashSet* hset = malloc(sizeof(HashSet));
    hset->capacidad = capacidad;
    hset->casillas = malloc(capacidad*sizeof(NodoHash*));
    for (int i = 0; i < capacidad; i++) {
        hset->casillas[i] = NULL;
    }
    return hset;
}

int contienehashset(HashSet* hset, char* clave) {
    unsigned long indice = hasheo(clave) % hset->capacidad;
    NodoHash* nodo = hset->casillas[indice];
    int encontrado=0;
    while (nodo && !encontrado) {
        if (strcmp(nodo->clave, clave) == 0){
         encontrado= 1;
        }
        nodo = nodo->sig;
    }
    return encontrado;
}

HashSet* insertarHashset(HashSet* hset, char* clave){
    if (contienehashset(hset, clave)){
        return hset;
    }
    unsigned long indice = hasheo(clave) % hset->capacidad;
    NodoHash* nodo = malloc(sizeof(NodoHash));
    nodo->clave = mi_strdup(clave);
    nodo->sig = hset->casillas[indice];
    hset->casillas[indice] = nodo;
    return hset;
}

void destruirHashSet(HashSet* hset){
    if (!hset){
        return;
    }
    for (int i = 0; i < hset->capacidad; i++){
        NodoHash* nodo = hset->casillas[i];
        while (nodo!=NULL) {
            NodoHash* siguiente = nodo->sig;
            free(nodo->clave); // liberar la cadena
            free(nodo);        // liberar el nodo
            nodo = siguiente;
        }
    }

    free(hset->casillas); // liberar el arreglo de casillas
    free(hset);           // liberar el hashset
}

