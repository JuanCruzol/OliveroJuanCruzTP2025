#include"apply.h"



int isValidApply(char* definicion, TablaHash* tabla_de_funciones,TablaHash* tabla_de_listas,int* pos_lista){
    int lista_valida=0;
    int indice=0;
    while(definicion[indice]!='\0'){
        indice++;
    }
    indice--;
    //legamos al final
    //ahora tiene q haber un ; y lo q sigua tiene q ser una lista de la forma [num,num,..]
    //o algo defino dentro de la tabala de listas
    while(0<indice && definicion[indice]==' '){
        indice--;
    }
    if(definicion[indice]!=';'){
        //no hay un ; al final, MAL
        return 0;
    }
    //lo sacamos al ; para q no moleste
    definicion[indice]=' ';

    //ahora vamos para atras para encontrar un ] o un numeros en char o un char de a-z/A-Z
    //cualquier otra cosa se considera invalida
    while(0<indice && definicion[indice]==' '){
        indice--;
    }
    if(definicion[indice]==']'){
        //vamos para atras hasta encontrar q se cierra el corchete
        //!indice esta porq si no esta puede haber un error por eso lo
        //consideramos
        while(0<indice && definicion[indice]!='['){
            indice--;
        }
        if(definicion[indice]=='['){
            if(Isvalidlis(definicion+indice,0,0,0,0)){
                //guardamos la posicion donde empezo
                *pos_lista=indice;
                lista_valida=1;
                //cortamos
                definicion[indice]='\0';
            }
            else{
                printf("lista invalida\n");
            }
        }
        
    }
    else if(isalpha(definicion[indice]) || isNumber(definicion[indice])){
        int fin=indice;
        while(0<indice && (isalnum(definicion[indice]) || definicion[indice]=='_')){
            indice--;
        }

        int inicio = indice+1;
        char nombre[128];
        strncpy(nombre, definicion+inicio, fin-inicio+1);
        nombre[fin-inicio+1]='\0';

        //buscamos ese nombre
        if(buscar(tabla_de_listas,nombre)!=NULL){
            //guardamos la posicion de lista
            *pos_lista=inicio;
            lista_valida=1;
            //cortamos 
            definicion[inicio]='\0';
        }
        else{
            printf("No existe esa lista\n");
        }
    }
    if(!lista_valida){
        
        //Si no es valida la lista no revisamos ya la funcion
        return lista_valida;//osea 0
    }
    //AHORA revisamos funciones
    //funcion q valida que sea un funcion

    return isValidoFun(definicion,tabla_de_funciones);
}

DList* pasar_a_lista(char* expresion_lista,TablaHash* tabla_de_listas){
    DList* estruc_lista=crear_list();
    //primero sacamos ;
    int indice=0;
    while(expresion_lista[indice]!='\0' && expresion_lista[indice]!=';'){
        indice++;
    }
    if(expresion_lista[indice]==';'){
        expresion_lista[indice]='\0';
    }
    //ahora la buscamos en la tabla de listas

    char* lista=buscar(tabla_de_listas,expresion_lista);
    if(lista==NULL){
        //no esta en la tabla osea q esat expresada de la forma [.....]

        lista=expresion_lista;
    }
    //esto es para no destruir la lista
    char copy[4096];
    strcpy(copy,lista);
    //como esto ya paso por una validacion de listas lo q hacemos es usar el tokes con "[]" , "," y ";"
    char* partes_numericas=strtok(copy,"[ ] , ;");
    while(partes_numericas!=NULL){
        int* valor_a_agregar = malloc(sizeof(int));
        *valor_a_agregar = atoi(partes_numericas);
        dlist_agregar_ultimo(&estruc_lista,(void*)valor_a_agregar,copyfisica);
        partes_numericas=strtok(NULL,"[ ] , ;");
    }
    return estruc_lista;
}

DList* aplicar_primitiva(char* comando,DList* lista){
    if(strcmp(comando,"0i")==0){
        cero_izq(&lista);
        
    }
    if(strcmp(comando,"0d")==0){
        cero_der(&lista);
    }
    if(strcmp(comando,"Si")==0){
        sucesor_izq(&lista);
    }
    if(strcmp(comando,"Sd")==0){
        sucesor_der(&lista);
    }
    if(strcmp(comando,"Di")==0){
        borrar_izq(&lista);
    }
    if(strcmp(comando,"Dd")==0){
        borrar_der(&lista);
    }
    return lista;
}

DList* aplicar_repeticion(DList* lista,char *comando,TablaHash* tabla_de_funciones){

    //esto por si esta vacia
    if(lista->primero == NULL || lista->ultimo == NULL){
        return lista;
    }
    int primero=*(int*)lista->primero->dato;
    int ultimo=*(int*)lista->ultimo->dato;
    if(primero == ultimo){
        return lista;
    }
    lista=aplicar_funcion_a_lista(lista,comando,tabla_de_funciones);
    return aplicar_repeticion(lista,comando,tabla_de_funciones);
}

DList* aplicar_funcion_a_lista(DList* lista, char* funcion,TablaHash* tabla_de_funciones){
    char copy[1024];
    strcpy(copy,funcion);
    int indice=0;
    char comando[1024];
    //lo usamos a pos para ir copiando las funciones de funciones de funcion
    int pos;
    int flag=1;
    while(copy[indice]!='\0' && flag){
        pos=0;
        //nos movemos al primer caracter de alguna de las funciones
        while(copy[indice]==' '){
            indice++;
        }

        if(copy[indice]=='\0'){
            flag=0;
        }
        else{
            while(copy[indice]!='\0' && copy[indice]!=' '){
                comando[pos]=copy[indice];
                pos++;
                indice++;
            }
            //cuando se rompa esto ya copiamos la primera funcion
            comando[pos]='\0';
            if(isPrimitiva(comando)){
                lista=aplicar_primitiva(comando,lista);
            }
            else{
                //la busacamos en la tabla
                char* funcion_extendida=buscar(tabla_de_funciones,comando);
                if(funcion_extendida!=NULL){
                    printf("%s\n",funcion_extendida);
                    lista=aplicar_funcion_a_lista(lista,funcion_extendida,tabla_de_funciones);
                }
                else{
                    //esto es para sacar los < >de la palabra
                    char limpio[1022];
                    strncpy(limpio,comando+1,pos-2);
                    limpio[pos-2]='\0';
                    //si no es una primitiva, ni una definida en la tabla, es porq es una del tipo <...>
                    lista=aplicar_repeticion(lista,limpio,tabla_de_funciones); //hacer
                }
            }
        }

    }
    return lista;
}

void imprimir_Lista(DList* lista){
    printf("[");
    DNodo* temp=lista->primero;
    while(temp!=NULL){
        if(temp->sig==NULL){
            printf(" %d ",*(int*)temp->dato);
            
        }
        else{
            printf(" %d, ",*(int*)temp->dato);
        }
        temp=temp->sig;
    }
    printf("]\n");
}

void funcion_apply(char* definicion, TablaHash* tabla_de_funciones,TablaHash* tabal_de_listas){
    int pos_lista;
    char copy[1024];
    strcpy(copy,definicion);
    if(!isValidApply(copy,tabla_de_funciones,tabal_de_listas,&pos_lista)){
        printf("DEfincion de apply incorecta\n");
        return;
    }

    DList* lista=pasar_a_lista(definicion+pos_lista,tabal_de_listas);
    char funciones[1024];
    strncpy(funciones,definicion,pos_lista);
    funciones[pos_lista]='\0';

    lista=aplicar_funcion_a_lista(lista,funciones,tabla_de_funciones);
    
    imprimir_Lista(lista);

    destruir_Dnodo_Dlist(lista,destroy);
}