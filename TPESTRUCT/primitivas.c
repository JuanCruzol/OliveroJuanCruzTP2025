#include"primitivas.h"
#include<stdlib.h>

void* copyfisica(void* dato){
    int* datoFisico=malloc(sizeof(int));
    *datoFisico=*(int*)dato;
    return datoFisico;
}

void cero_izq(DList** list){
    int valor_agregar=0;
    dlist_agregar_primero(list,(void*)&valor_agregar,copyfisica);
}

void cero_der(DList** list){
    int valor_agregar=0;
    dlist_agregar_ultimo(list,(void*)&valor_agregar,copyfisica);
}

void sucesor_izq(DList** list){
    if((*list)->primero==NULL){
        return;
    }
    (*(int*)((*list)->primero)->dato)++;
}

void sucesor_der(DList** list){
    if((*list)->primero==NULL){
        return;
    }
    (*(int*)((*list)->ultimo)->dato)++;
}

void borrar_izq(DList** list){
    if((*list)->primero==NULL){
        return;
    }
    if((*list)->primero->sig==(*list)->ultimo){
        (*list)->ultimo=NULL;
    }
    DNodo* nodo_a_eliminar=(*list)->primero;
    
    if ((*list)->primero==(*list)->ultimo) {
        (*list)->ultimo=NULL;
        (*list)->primero=NULL;
    } else {
        (*list)->primero=nodo_a_eliminar->sig;
        (*list)->primero->ant=NULL;
    }
    free(nodo_a_eliminar);
}

void borrar_der(DList** list){
    if((*list)->primero==NULL){
        return;
    }
    DNodo* nodo_a_eliminar=(*list)->ultimo;

    // Caso: un solo nodo
    if ((*list)->primero==(*list)->ultimo) {
        (*list)->primero=NULL;
        (*list)->ultimo=NULL;
    } else {
        (*list)->ultimo=nodo_a_eliminar->ant;
        (*list)->ultimo->sig=NULL;
    }

    free(nodo_a_eliminar);
}
