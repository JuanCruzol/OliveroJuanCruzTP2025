#include "cola.h"
#include<stdio.h>
#include<stdlib.h>

Cola crear_cola(){
    Cola cola=malloc(sizeof(DList));
    cola->primero=NULL;
    cola->ultimo=NULL;
    return cola;
}

Cola agregar_dato_prioridad(Cola cola,void* dato,FuncioneCopia copy){
    DNodo* nuevo_nodo=malloc(sizeof(DNodo));
    nuevo_nodo->dato=copy(dato);
    nuevo_nodo->sig=cola->primero;
    if(cola->ultimo==NULL){
        cola->ultimo=nuevo_nodo;
    }
    cola->primero=nuevo_nodo;
    return cola;
}

Cola cola_encolar(Cola cola,void* dato,FuncioneCopia copy){
    DNodo* nuevo_nodo=malloc(sizeof(DNodo));
    if(!nuevo_nodo){
        return NULL;
    }
    nuevo_nodo->dato=copy(dato);
    nuevo_nodo->sig=NULL;
    if(cola->primero==NULL){
        cola->primero=nuevo_nodo;
        cola->ultimo=nuevo_nodo;
    }
    else{
        cola->ultimo->sig=nuevo_nodo;
        cola->ultimo=nuevo_nodo;
    }
    return cola;
}

int cola_vacia(Cola cola){
    return(cola->primero==NULL);
}

void* cola_desencolar(Cola cola){
    if(cola->primero==NULL){
        return NULL;
    }
    DNodo* nodo_a_eliminar=cola->primero;
    void* dato =nodo_a_eliminar->dato;
    cola->primero=cola->primero->sig;

    free(nodo_a_eliminar);
    return dato;
}

void* cola_inicio(Cola cola){
    if(cola->primero!=NULL){
        return cola->primero->dato;
    }
    return NULL;
    
}

void cola_imprimir(Cola cola, FuncioneVisitante f){
    DNodo* temp=cola->primero;
    for(;temp!=NULL;temp=temp->sig){
        f(temp->dato);
    }
}

void cola_destruir(Cola cola,FuncionDestructora destroy){
    DNodo* temp=cola->primero;
    DNodo* nodo_a_eliminar;
    while(temp!=NULL){
        nodo_a_eliminar=temp;
        temp=temp->sig;
        destroy(nodo_a_eliminar->dato);
        free(nodo_a_eliminar); 
    }
    free(cola);
}
