#include<stdio.h>
#include<stdlib.h>
#include"dlist.h"

DNodo* crear_nodo(){
    return NULL;
}

DList* crear_list(){
    DList * list=malloc(sizeof(DList)); 
    list->primero=NULL;
    list->ultimo=NULL;
    return list;
}

void dlist_agregar_primero(DList** list,void* dato,FuncionCopia copy){
    DNodo* nodo=(*list)->primero;
    DNodo* nuevo_nodo=malloc(sizeof(DNodo));
    nuevo_nodo->dato=copy(dato);
    nuevo_nodo->ant=NULL;
    nuevo_nodo->sig=(nodo);
    if((nodo)!=NULL){
        (nodo)->ant=nuevo_nodo;
        (nodo)=nuevo_nodo;  
    }
    if((nodo)==NULL){
        (*list)->ultimo=nuevo_nodo;
    }
    (*list)->primero=nuevo_nodo;
    
}

void dlist_agregar_ultimo(DList** list,void* dato,FuncionCopia copy){
    DNodo* temp=(*list)->primero;
    DNodo* nuevo_nodo=malloc(sizeof(DNodo));
    nuevo_nodo->dato=copy(dato);
    nuevo_nodo->sig=NULL;
    if(temp==NULL){
        nuevo_nodo->ant=NULL;
        (*list)->primero=nuevo_nodo;
        (*list)->ultimo=nuevo_nodo;
    }
    else{
    for(;temp->sig!=NULL;temp=temp->sig);

    temp->sig=nuevo_nodo;
    nuevo_nodo->ant=temp;
    (*list)->ultimo=nuevo_nodo;
    }
}

void dnodo_recorrer(DList* list,FuncionVisitante f){
    DNodo* temp=list->primero;
    for(;temp!=NULL;temp=temp->sig){
        f(temp->dato);
    }
}

void destruir_Dnodo_Dlist(DList* list,FuncionDestructora destruc){
    DNodo* nodo=list->primero;
    DNodo* temp;
    for(;nodo!=NULL;){
        temp=nodo;
        nodo=nodo->sig;
        destruc(temp->dato);
        free(temp);
    }
    free(list);
}

int Dlist_vacia(DList* list){
    return (list->primero==NULL);
}