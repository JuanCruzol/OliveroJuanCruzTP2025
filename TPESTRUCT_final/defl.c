#include"defl.h"

int isNumber(char fragmento){
    return (48<=fragmento && fragmento<=57);
}


int Isvalidlis(char* definicion,int espero_coma,int espero_num,int indice,int list_vacia){
    if(definicion[indice]=='\0' || definicion[indice]==';'){
        //no hay nada
        return 0;
    }
    else if(definicion[indice]=='['){
        //encontre un espacio
        return Isvalidlis(definicion,0,1,indice+1,1);
    }
    else if(definicion[indice]==']' && list_vacia){
        //caso de lista vacia
        definicion[indice+1]='\0';
        return 1;
    }
    else if(definicion[indice]==']' && espero_coma){
        //fin de la lista
        
        return 1;
    }
    else if(isNumber(definicion[indice]) && espero_num){
        //me encontre un numero y estaba esperando numero
        //ahora puede seguir un numero o una coma, y la lisat no puede ser vacia ya
        return Isvalidlis(definicion,1,1,indice+1,0);
    }
    else if(definicion[indice]==' '){
        //hay un esapcio, sigo
        return Isvalidlis(definicion,espero_coma,espero_num,indice+1,list_vacia);
    }
    else if(definicion[indice]==',' && espero_coma){
        //me cruce con una coma cuando la esperaba, ahora no espero otra coma, sino un numero
        return Isvalidlis(definicion,0,1,indice+1,0);
    }
    else{
        //aca cae todo lo q no se cumple
        return 0;
    }

}

TablaHash* funcion_defl(char* Comando,TablaHash* Tabla_de_listas){
    Comando=strtok(NULL," =");
    if(buscar(Tabla_de_listas,Comando)!=NULL){
        printf("Lista ya definida\n");
        return Tabla_de_listas;
    }
    char nombre_Lis[64];
    strcpy(nombre_Lis,Comando);//guardamos el nombre
    Comando=strtok(NULL,"=");
    
    char definicion[1024];
    strcpy(definicion,Comando);

    if(!Isvalidlis(definicion,0,0,0,0)){
        printf("definicion de lista invalida!!\n");
        return Tabla_de_listas;
    }
    printf("Lista Guardada!\n");

    insertar(&Tabla_de_listas,nombre_Lis,definicion);
    return Tabla_de_listas;
}