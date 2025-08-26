#include"primitivas.h"

#include<stdio.h>
#include<stdlib.h>

void printear(void* data){
    printf("%d\n",*(int*)data);
}



void destrucdummy(void* dato){
    free(dato);
}

int main(){
    DList* nlist=crear_list();
    if(Dlist_vacia(nlist)){
        printf("Lista Vacia!\n");
        cero_der(&nlist);
        sucesor_der(&nlist);
        sucesor_der(&nlist);
        borrar_der(&nlist);
        cero_izq(&nlist);
        printf("LISTO\n");
        dnodo_recorrer(nlist,printear);
        printf("SI\n");
        destruir_Dnodo_Dlist(nlist,destrucdummy);
    }
    return 0;
}