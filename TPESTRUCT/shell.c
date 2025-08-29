#include"shell.h"
#include<stdio.h>
#include"comandos.h"
#include<string.h>
#include"hash.h"

#define MAXBUFF 4096 //4KB, usado normalmente en otros interepretes
#define PRIMOINICIAL 1019 // con este primo inicializaremos las 2 tablas hash


void iniciar_shell(){
    int trabajo=1;
    char comando[MAXBUFF];
    printf("BIENVENIDO AL INTERPRETE DE LISTAS!!!\n");
    TablaHash* Tabla_de_funciones= inicializarHash(PRIMOINICIAL);
    TablaHash* Tabla_de_listas= inicializarHash(PRIMOINICIAL);
    while(trabajo){
        printf(">>");
        scanf(" %[^\n]",comando);
        char* Partes=strtok(comando," =");
        if(Partes==NULL){
            printf("Comando invalido");
        }
        if(strcmp(Partes,"deff")==0){
            Tabla_de_funciones=funcion_deff(Partes,Tabla_de_funciones);
        }
        else if(strcmp(Partes,"defl")==0){
            Tabla_de_listas=funcion_defl(Partes,Tabla_de_listas);
        }
        else if(strcmp(Partes,"apply")==0){
            int indice=0;
            while(comando[indice]!='a'){
                indice++;
            }
            //esto es para empezar depues del apply
            funcion_apply(comando+indice+6,Tabla_de_funciones,Tabla_de_listas);
        }
        else if(strcmp(Partes,"search")==0){
            //completar
        }
        else if(strcmp(Partes,"salir")==0){
            printf("Salieno del interprete...\n");
            //LIMPIAR HASH!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            liberarHash(Tabla_de_funciones);
            printf("CHECK\n");
            liberarHash(Tabla_de_listas);
            trabajo=0;
        }
        else{
            printf("Comando Invalido");
        }
    }
}

int main(){
    printf("INICIANDO INTERPRETE DE LISTA!!\n");
    iniciar_shell();
    return 1;
}