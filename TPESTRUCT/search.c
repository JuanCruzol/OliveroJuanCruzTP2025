#include"search.h"
#define MAX_ITER 100000

void* coppySimbolica(void* dato){
    return dato;
}

int verificar_search(char* comando, TablaHash* tabla_de_listas,Estado** listas_izq,Arreglo_Dlist** listas_der){
    
    int indice=0;
    //usaremos esto para verificar la lista
    int inicio,fin;
    int llaves_validas=0;
    int flag=1;
    while(comando[indice]!='\0' && comando[indice]==' '){
        indice++;
    }

    if(comando[indice]!='{'){
        return 0;
    }
    indice++;
    while(comando[indice]!='\0' && flag && !llaves_validas){
        //salteemos todos los espacios hasta llegar a un caracter no vacio
        while(comando[indice]!='\0' && comando[indice]==' '){
            indice++;
        }
        if(comando[indice]=='\0'){
            //esta ma;
            flag=0;
        }
        //hay o [] o una defincion,
        else{
            char lista_a_verificar1[2045];
            inicio=indice;
            if(comando[indice]=='['){
                //puede ser una lista de la forma [], avanzemos hasta encontrar un ]
                while(comando[indice]!='\0' && comando[indice]!=']'){
                    indice++;
                }
                if(comando[indice]=='\0'){
                    //no valido, nunca se cerro;
                    flag=0;
                }
                else{
                    fin=indice;
                    strncpy(lista_a_verificar1,comando+inicio,fin-inicio+1);
                    lista_a_verificar1[fin-inicio+1]='\0';
                    
                }
            }
            //es un caracter distinto de [, puede ser una definicion, avanzemos hasta la ','/' ' o hasta '\0'
            else{
                while(comando[indice]!='\0' && comando[indice]!=',' && comando[indice]!=' '){
                    indice++;
                }
                if(comando[indice]=='\0'){
                    //no valido, nunca se cerro;
                    flag=0;
                }
                else{
                    //bajamos en uno pues estamos parados en la coma o en el espacio
                    fin=indice-1;
                    strncpy(lista_a_verificar1,comando+inicio,fin-inicio+1);
                    lista_a_verificar1[fin-inicio+1]='\0';
                }
            }
            if(!Isvalidlis(lista_a_verificar1,0,0,0,0) && buscar(tabla_de_listas,lista_a_verificar1)==NULL){
                flag=0;
            }
            else{
                //la primera lista fue valida!! 
                //lo guardamo en estado, ams especifico en la lista de dlist
                
                (*listas_izq)=agregar_lista_a_estado(*listas_izq,lista_a_verificar1,tabla_de_listas);

                //avanzemos hasta encontrar una coma o el '\0'
                while(comando[indice]!='\0' && comando[indice]!=','){
                    indice++;
                }
                if(comando[indice]=='\0'){
                    //no hay coma
                    flag=0;
                }
                else{
                    //hay coma, mismo procedimiento q lo anterior
                    indice++;
                    //saltamos todos los espacios
                    while(comando[indice]!='\0' && comando[indice]==' '){
                        indice++;
                    }
                    if(comando[indice]=='\0'){
                        flag=0;
                    }
                    else{
                        char lista_a_verificar[2045];
                        inicio=indice;
                        if(comando[indice]=='['){
                            //puede ser una lista de la forma [], avanzemos hasta encontrar un ]
                            while(comando[indice]!='\0' && comando[indice]!=']'){
                                indice++;
                            }
                            if(comando[indice]=='\0'){
                                //no valido, nunca se cerro;
                                flag=0;
                            }
                            else{
                                fin=indice;
                                strncpy(lista_a_verificar,comando+inicio,fin-inicio+1);
                                lista_a_verificar[fin-inicio+1]='\0';
                                indice++;
                            }
                        }
                        //es un caracter distinto de [, puede ser una definicion, avanzemos hasta la ';'/'}' o hasta '\0'
                        else{
                            while(comando[indice]!='\0' && comando[indice]!=' ' && comando[indice]!=';' && comando[indice]!='}'){
                                indice++;
                            }
                            if(comando[indice]=='\0'){
                                //no valido, nunca se cerro;
                                flag=0;
                            }
                            else{
                                //bajamos en uno pues estamos parados en la coma o en el espacio
                                fin=indice-1;
                                strncpy(lista_a_verificar,comando+inicio,fin-inicio+1);
                                lista_a_verificar[fin-inicio+1]='\0';
                            }
                        }
                        if(!Isvalidlis(lista_a_verificar,0,0,0,0) && buscar(tabla_de_listas,lista_a_verificar)==NULL){
                            flag=0;
                        }
                        else{
                            //la segunda lista resulta valida, 
                            //lo guardamos en listas_der
                            (*listas_der)=agregar_a_lista_de_listas(*listas_der,tabla_de_listas,lista_a_verificar);
                            //avanazamos ahora, donde si hay una ";" sigue el bucle, 
                            //si hay una "}" cerramos bucle y verificamos q termine bien, cualquier otra cosa, esta mal
                            while(comando[indice]!='\0' && comando[indice]!='}' && comando[indice]!=';'){
                                indice++;
                            }
                            if(comando[indice]==';'){
                                indice++;
                                //seguimos
                            }
                            else if(comando[indice]=='}'){
                                llaves_validas=1;
                            }
                            else{
                                //otra cosa
                                flag=0;
                            }
                        }
                    }
                }
            }
        }
    }
    if(!llaves_validas){
        //bandera es 0 o llegamos al final
        return 0;
    }
    //nos movemos desp del }
    indice++;

    while(comando[indice]!='\0' && comando[indice]==' '){
        indice++;
    }
    if(comando[indice]!=';'){
        destruir_estado(*listas_izq);
        destruir_lista_de_lista(*listas_der);
        return 0;
    }
    //nos movems una desp
    indice++;
    //ahora veamos q no haya nada raro
    while(comando[indice]!='\0' && comando[indice]==' '){
        indice++;
    }
    if(comando[indice]!='\0'){
        destruir_estado(*listas_izq);
        destruir_lista_de_lista(*listas_der);
        return 0;
    }
    return 1;
}


Estado* crear_estado(){
    Estado* nuevo_estado=malloc(sizeof(Estado));
    //cantidad inicial para nuestro array de listas
    nuevo_estado->cant_max=10000;
    nuevo_estado->size=0;
    nuevo_estado->lista_de_lista=malloc(sizeof(DList*)*nuevo_estado->cant_max);
    for(int i=0;i<nuevo_estado->cant_max;i++){
        nuevo_estado->lista_de_lista[i]=NULL;
    }
    nuevo_estado->cadena_formada=malloc(sizeof(char)*100);
    nuevo_estado->cadena_formada[0]='\0';

    return nuevo_estado;
}

void destruir_estado(Estado* estado){
    free(estado->cadena_formada);
    for(int i=0;i<estado->size;i++){
        destruir_Dnodo_Dlist(estado->lista_de_lista[i],free);
    }
    free(estado->lista_de_lista);
    free(estado);
}

Estado* agregar_lista_a_estado(Estado* estado,char lista_a_agregar[],TablaHash* tabla_de_listas){
    if(estado->size>=estado->cant_max){
        int viejo_max=estado->cant_max;
        estado->cant_max=estado->cant_max*10;
        estado->lista_de_lista=realloc(estado->lista_de_lista,sizeof(DList*)*estado->cant_max);
        for(int i=viejo_max;i<estado->cant_max;i++){
            estado->lista_de_lista[i]=NULL;
        }
    }
    (estado->lista_de_lista[estado->size])=pasar_a_lista(lista_a_agregar,tabla_de_listas);
    estado->size++;
    return estado;
}

Estado* copiar_estado(Estado* estado){
    Estado* nuevo_estado=crear_estado();
    strcpy(nuevo_estado->cadena_formada,estado->cadena_formada);
    nuevo_estado->cant_max=estado->cant_max;
    nuevo_estado->size=estado->size;
    for(int i=0;i<nuevo_estado->size;i++){
        nuevo_estado->lista_de_lista[i]=copia_dlist(estado->lista_de_lista[i]);
    }
    return nuevo_estado;
}

Estado* aplicar_funcion_a_estado(Estado* actual_esatado, char* funcion_a_aplicar, TablaHash* tabla_de_funciones){
    strcat(actual_esatado->cadena_formada," ");
    strcat(actual_esatado->cadena_formada,funcion_a_aplicar);
    for(int i=0;i<actual_esatado->size;i++){
        actual_esatado->lista_de_lista[i]=aplicar_funcion_a_lista(actual_esatado->lista_de_lista[i],funcion_a_aplicar,tabla_de_funciones);
    }
    return actual_esatado;
}

Arreglo_Dlist* inicializar_lista_de_lista(){
    Arreglo_Dlist * nueva_l_de_l=malloc(sizeof(Arreglo_Dlist));
    nueva_l_de_l->cant_max=10000;
    nueva_l_de_l->size=0;
    nueva_l_de_l->lista_de_lista=malloc(sizeof(DList*)*nueva_l_de_l->cant_max);
    for(int i=0;i<nueva_l_de_l->cant_max;i++){
        nueva_l_de_l->lista_de_lista[i]=NULL;
    }
    return nueva_l_de_l;
}

void destruir_lista_de_lista(Arreglo_Dlist* l_d_l){
    for(int i=0;i<l_d_l->size;i++){
        destruir_Dnodo_Dlist(l_d_l->lista_de_lista[i],free);
    }
    free(l_d_l->lista_de_lista);
    free(l_d_l);
}

Arreglo_Dlist* agregar_a_lista_de_listas(Arreglo_Dlist* l_de_l,TablaHash* tabla_de_listas,char lista_a_agregar[]){
    if(l_de_l->size>=l_de_l->cant_max){
        int viejo_max=l_de_l->cant_max;
        l_de_l->cant_max=l_de_l->cant_max*10;
        l_de_l->lista_de_lista=realloc(l_de_l->lista_de_lista,sizeof(DList*)*l_de_l->cant_max);
        for(int i=viejo_max;i<l_de_l->cant_max;i++){
            l_de_l->lista_de_lista[i]=NULL;
        }
    }
    (l_de_l->lista_de_lista[l_de_l->size])=pasar_a_lista(lista_a_agregar,tabla_de_listas);
    l_de_l->size++;
    return l_de_l;
}

int listas_iguales(DList* lista1,DList* lista2){
    DNodo* temp1=lista1->primero;
    DNodo* temp2=lista2->primero;
    int dato1,dato2;
    int iguales=1;
    while(temp1!=NULL && temp2!=NULL && iguales){
         dato1=*(int*)temp1->dato;
         dato2=*(int*)temp2->dato;
        if(dato1!=dato2){
            iguales=0;
        }
        else{
            temp1=temp1->sig;
            temp2=temp2->sig;
        }
    }
    return temp1==NULL && temp2==NULL;
}

int lista_de_listas_iguales(DList** lista_de_lista1,DList** lista_de_lista2,int size){
    int indice=0;
    int iguales=1;
    while(indice<size && iguales){
        if(!listas_iguales(lista_de_lista1[indice],lista_de_lista2[indice])){
            //no son iguales, salimos
            iguales=0;
        }
        else{
            //son iguales, pasamos a la siguente
            indice++;
        }
    }
    return iguales;
}



void buscar_solucion(Estado* estado_init,Arreglo_Dlist* l_de_l,TablaHash* tabla_de_funciones){
    Cola cola_estados=crear_cola();

    cola_estados=cola_encolar(cola_estados,estado_init,coppySimbolica);

    HashSet* listas_visitadas=crear_hashset(100);
    listas_visitadas=insertarHashset(listas_visitadas,estado_init->cadena_formada);
    
    int solucion_encontrada=0;
    int numero_de_iteracion=0;
    while(!cola_vacia(cola_estados) && !solucion_encontrada && numero_de_iteracion<MAX_ITER){
        Estado* estado_actual=cola_desencolar(cola_estados);
        if(lista_de_listas_iguales(estado_actual->lista_de_lista,l_de_l->lista_de_lista,l_de_l->size)){
            solucion_encontrada=1;
            printf("SE encontra funcionen la iteracion:%d\n->%s\n",numero_de_iteracion,estado_actual->cadena_formada);
            destruir_estado(estado_actual);
        }
        else{
            char* funciones_a_aplicar[]={"0i","0d","Si","Sd","Dd","Di"};
            for(int i=0;i<6;i++){
                Estado* siguiente_estado=copiar_estado(estado_actual);
                siguiente_estado=aplicar_funcion_a_estado(siguiente_estado,funciones_a_aplicar[i],tabla_de_funciones);
                if(contienehashset(listas_visitadas,siguiente_estado->cadena_formada)){
                    destruir_estado(siguiente_estado);
                }
                else{
                    cola_estados=cola_encolar(cola_estados,siguiente_estado,coppySimbolica);
                }
            }
            //ahora a la tabla
            for(size_t j=0;j<tabla_de_funciones->size;j++){
                Hashcasillas* funcion_definida=&(tabla_de_funciones->casillas[j]);
                if(funcion_definida->ocupado){
                    Estado* siguiente_estado=copiar_estado(estado_actual);
                    siguiente_estado= aplicar_funcion_a_estado(siguiente_estado,funcion_definida->nombre,tabla_de_funciones);
                    if(contienehashset(listas_visitadas,siguiente_estado->cadena_formada)){
                        destruir_estado(siguiente_estado);
                    }
                    else{
                        cola_estados=cola_encolar(cola_estados,siguiente_estado,coppySimbolica);
                    }
                }
            }

            destruir_estado(estado_actual);
        }
        numero_de_iteracion++;
    }
    while(!cola_vacia(cola_estados)){
        Estado* esatdo_a_destruir=cola_desencolar(cola_estados);
        destruir_estado(esatdo_a_destruir);
    }
    cola_destruir(cola_estados,free);
    destruirHashSet(listas_visitadas);
    destruir_lista_de_lista(l_de_l);
    if(!(numero_de_iteracion<MAX_ITER)){
        printf("se llego al maximo de iteraciones\n");
    }
}


void funcion_search(char* comando, TablaHash* tabla_de_listas,TablaHash* tabla_de_funciones){
    Estado* estado_init=crear_estado();
    Arreglo_Dlist* l_de_l=inicializar_lista_de_lista();
    if(!verificar_search(comando,tabla_de_listas,&estado_init,&l_de_l)){
        printf("Comando search invalido!\n");
    }
    buscar_solucion(estado_init,l_de_l,tabla_de_funciones);

}