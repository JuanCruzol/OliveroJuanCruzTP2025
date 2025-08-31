#include"shell.h"


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
        if(fgets(comando,MAXBUFF,stdin)==NULL){
            printf("Error\n");
        }
        else{
            comando[strcspn(comando, "\n")] = '\0';

            char copia[MAXBUFF];
            strcpy(copia, comando);
            char* Partes = strtok(copia, " =");
            if(Partes==NULL){
                printf("Comando invalido");
            }
            
            if(strcmp(Partes,"deff")==0){
                if(verificacion_De_Comando(comando)){
                    Tabla_de_funciones=funcion_deff(Partes,Tabla_de_funciones);
                }
                else{
                    printf("No validp\n");
                }
            }
            else if(strcmp(Partes,"defl")==0){
                if(verificacion_De_Comando(comando)){
                    Tabla_de_listas=funcion_defl(Partes,Tabla_de_listas);
                }
                else{
                    printf("No validp\n");
                }
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
                liberarHash(Tabla_de_listas);
                trabajo=0;
            }
        else{
            printf("Comando Invalido\n");
        }
    }
    }
}

int main(){
    printf("INICIANDO INTERPRETE DE LISTA!!\n");
    iniciar_shell();
    return 1;
}