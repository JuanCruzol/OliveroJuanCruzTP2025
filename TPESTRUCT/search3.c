#include"search3.h"


Estado* inicializar_esatdo(){
    Estado* nuevo_estado=malloc(sizeof(Estado));
    nuevo_estado->cadena_formada=malloc(sizeof(char)*1024);
    nuevo_estado->cadena_formada[0]='\0';
    nuevo_estado->cant_max=10000;
    nuevo_estado->size=0;
    nuevo_estado->lista_de_lista=malloc(sizeof(DList*)*nuevo_estado->cant_max);
    for(int i=0;i<nuevo_estado->cant_max;i++){
        nuevo_estado->lista_de_lista[i]=NULL;
    }
    return nuevo_estado;
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

DNodo* copiar_nodo(DNodo* nodo) {
    if (!nodo) return NULL;
    DNodo* nuevo = malloc(sizeof(DNodo));
    nuevo->dato = malloc(sizeof(int)); 
    *(int*)nuevo->dato = *(int*)nodo->dato;
    nuevo->sig = copiar_nodo(nodo->sig);
    nuevo->ant = NULL;
    if (nuevo->sig) nuevo->sig->ant = nuevo;
    return nuevo;
}

DList* copiar_lista(DList* lista){
    DList* nueva = malloc(sizeof(DList));
    nueva->primero = copiar_nodo(lista->primero);

    DNodo* temp = nueva->primero;
    nueva->ultimo = NULL;
    while(temp) {
        nueva->ultimo = temp;
        temp = temp->sig;
    }
    return nueva;
}


Estado* copiar_estado(Estado* original) {
    if (!original) return NULL;

    Estado* copia = malloc(sizeof(Estado));
    copia->size = original->size;
    copia->cant_max = original->cant_max;

    copia->cadena_formada = malloc(strlen(original->cadena_formada) + 1);
    strcpy(copia->cadena_formada, original->cadena_formada);
    
    // Copiar arreglo de listas
    copia->lista_de_lista = malloc(sizeof(DList*) * original->cant_max);
    for (int i=0; i<original->size; i++) {
        if (original->lista_de_lista[i]) {
            copia->lista_de_lista[i] = copiar_lista(original->lista_de_lista[i]);
        } else {
            copia->lista_de_lista[i] = NULL;
        }
    }
    // inicializar el resto a NULL
    for (int i=original->size; i<original->cant_max; i++) {
        copia->lista_de_lista[i] = NULL;
    }

    return copia;
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

Arreglo_Dlist* agregar_a_lista_de_listas(Arreglo_Dlist* l_de_l,TablaHash* tabla_de_listas,char lista_a_agregar[]){
    if(l_de_l->size>=l_de_l->cant_max){
        int viejo_max=l_de_l->cant_max;
        l_de_l->cant_max=l_de_l->cant_max*10;
        l_de_l->lista_de_lista=realloc(l_de_l->lista_de_lista,sizeof(DList*)*l_de_l->cant_max);
        for(int i=viejo_max;i<l_de_l->cant_max;i++){
            l_de_l->lista_de_lista[i]=NULL;
        }
    }
    l_de_l->lista_de_lista[l_de_l->size]=pasar_a_lista(lista_a_agregar,tabla_de_listas);
    l_de_l->size++;
    return l_de_l;
}

void destruir_estado(Estado* estado){
    if(!estado){
        return ;
    }
    if (estado->cadena_formada) {
        free(estado->cadena_formada);
    }
    if (estado->lista_de_lista) {
        for (int i = 0; i < estado->size; i++) {
            if (estado->lista_de_lista[i]) {
                destruir_Dnodo_Dlist(estado->lista_de_lista[i],free);
            }
        }
        free(estado->lista_de_lista);
    }
    free(estado);
}

void destruir_lista_de_lista(Arreglo_Dlist* l_de_l){
    for(int i=0;i<l_de_l->size;i++){
        destruir_Dnodo_Dlist(l_de_l->lista_de_lista[i],free);
    }
    free(l_de_l->lista_de_lista);
    free(l_de_l);
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

void* coppyDummy(void* data){
    return data;
}
void destructDummy(void* data){
    destruir_estado((Estado*)data);
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

Estado* aplicar_funcion_a_estado(Estado* actual_esatado, char* funcion_a_aplicar, TablaHash* tabla_de_funciones) {
    Estado* nuevo_estado = copiar_estado(actual_esatado);
    
    int len_actual = strlen(nuevo_estado->cadena_formada);
    int nueva_longitud = len_actual + strlen(funcion_a_aplicar) + 2;

    if (nueva_longitud > len_actual) {
        char* nueva_cadena = realloc(nuevo_estado->cadena_formada, nueva_longitud);
        if (!nueva_cadena) {
            destruir_estado(nuevo_estado);
            return NULL;
        }
        nuevo_estado->cadena_formada = nueva_cadena;
    }
    
    if (len_actual > 0) {
        strcat(nuevo_estado->cadena_formada, " ");
    }
    strcat(nuevo_estado->cadena_formada, funcion_a_aplicar);
    
    for (int i = 0; i < nuevo_estado->size; i++) {
        if (nuevo_estado->lista_de_lista[i]) {
            nuevo_estado->lista_de_lista[i] = aplicar_funcion_a_lista(nuevo_estado->lista_de_lista[i], funcion_a_aplicar, tabla_de_funciones);
        }
    }
    
    return nuevo_estado;
}

void buscar_solucion(Estado* estado_init,Arreglo_Dlist* l_de_l,TablaHash* tabla_de_funciones){
    Cola cola_de_estados = crear_cola();

    cola_encolar(cola_de_estados,estado_init,coppyDummy);

    HashSet* visitados=crear_hashset(100);

    visitados=insertarHashset(visitados,estado_init->cadena_formada);

    int solucion_encontrada=0;
    while(!cola_vacia(cola_de_estados) && !solucion_encontrada){
        Estado* estado_actual= (Estado*)cola_desencolar(cola_de_estados);

        if(lista_de_listas_iguales(estado_actual->lista_de_lista,l_de_l->lista_de_lista,estado_actual->size)){

            solucion_encontrada=1;
            printf("funcion encontrada ----->%s\n",estado_actual->cadena_formada);
            destruir_estado(estado_actual);
        }
        else{
            //no son iguales, apliquemos funciones primitivas y de la tabla
            
            for(int i=0;i<7;i++){
                Estado* siguente_esatdo=copiar_estado(estado_actual);
                if(i==0){
                    //aplicamos 0i al estado actual
                    siguente_esatdo=aplicar_funcion_a_estado(siguente_esatdo,"0i",tabla_de_funciones);
                    
                }
                else if(i==1){
                    //aplicamos 0d al esado actual
                    siguente_esatdo=aplicar_funcion_a_estado(siguente_esatdo,"0d",tabla_de_funciones);
                }
                else if(i==2){
                    //aplicamos Si al esado actual
                    siguente_esatdo=aplicar_funcion_a_estado(siguente_esatdo,"Si",tabla_de_funciones);
                }
                else if(i==3){
                    //aplicamos Sd al esado actual
                    siguente_esatdo=aplicar_funcion_a_estado(siguente_esatdo,"Sd",tabla_de_funciones);
                }
                else if(i==4){
                    //aplicamos Di al esado actual
                    siguente_esatdo=aplicar_funcion_a_estado(siguente_esatdo,"Di",tabla_de_funciones);
                }
                else if(i==5){
                    //aplicamos Dd al esado actual
                    siguente_esatdo=aplicar_funcion_a_estado(siguente_esatdo,"Dd",tabla_de_funciones);
                }
                else if(i==6){
                    //aplicamos las funciones definidas al esado actual
                    for(size_t j=0;j<(tabla_de_funciones->size);j++){
                        Hashcasillas* funcion_definida=&tabla_de_funciones->casillas[j];
                        if(funcion_definida->ocupado){
                            //la casilla no esta vacia
                            siguente_esatdo=aplicar_funcion_a_estado(estado_actual,funcion_definida->definicion,tabla_de_funciones);
                        }
                    }
                    
                }
                if(siguente_esatdo && !contienehashset(visitados,siguente_esatdo->cadena_formada)){
                    cola_de_estados= cola_encolar(cola_de_estados,siguente_esatdo,coppyDummy);
                    visitados=insertarHashset(visitados,siguente_esatdo->cadena_formada);
                
                }
                destruir_estado(siguente_esatdo);
                }
        
            destruir_estado(estado_actual);
        }
    }
    while (!cola_vacia(cola_de_estados)) {
        Estado* estado_pendiente = (Estado*)cola_desencolar(cola_de_estados);
        destruir_estado(estado_pendiente);
    }
    cola_destruir(cola_de_estados,destructDummy);
    destruirHashSet(visitados);
    if(!solucion_encontrada){
        printf("no se pudo encontrar una solucion");
    }
    
}

void funcion_search(char* comando, TablaHash* tabla_de_listas,TablaHash* tabla_de_funciones){
    Estado* estado_init=inicializar_esatdo();
    Arreglo_Dlist* l_de_l=inicializar_lista_de_lista();
    if(!verificar_search(comando,tabla_de_listas,&estado_init,&l_de_l)){
        printf("Comando search invalido!\n");
    }
    buscar_solucion(estado_init,l_de_l,tabla_de_funciones);

}