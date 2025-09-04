#include<stdio.h>
#include<string.h>
#include<stdlib.h>



int main(){
    char buff[1024];
    scanf(" %[^\n]",buff);
    char* partes_numericas=strtok(buff,"[ ] , ;");
    while(partes_numericas!=NULL){
        int valor_a_agregar = atoi(partes_numericas);
        printf("%d\n",valor_a_agregar);
        partes_numericas=strtok(NULL,"[ ] , ;");
    }
    return 0;
}