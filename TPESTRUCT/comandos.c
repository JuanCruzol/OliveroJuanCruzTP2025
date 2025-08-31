#include"comandos.h"

int verificacion_De_Comando(char* comando){
    char palabra[16];    // "deff" o "defl"
    char nombre[128];    // nombre de función o lista
    char resto[4096];    // todo lo que sigue después del '='

    int n = sscanf(comando, " %15s %127[^=]= %4095[^\n]", palabra, nombre, resto);
    if (n != 3) {
        return 0; // no se pudo leer correctamente
    }

    // Limpiar espacios al inicio y fin del nombre
    int inicio = 0, fin = strlen(nombre) - 1;
    while (isspace(nombre[inicio])) inicio++;
    while (fin >= inicio && isspace(nombre[fin])) fin--;
    nombre[fin + 1] = '\0';
    if (inicio > 0) memmove(nombre, nombre + inicio, fin - inicio + 2);

    // Verificar palabra
    if (strcmp(palabra, "deff") != 0 && strcmp(palabra, "defl") != 0)
        return 0;

    // Verificar nombre no vacío
    if (strlen(nombre) == 0)
        return 0;

    // Verificar resto no vacío
    if (strlen(resto) == 0)
        return 0;
    //ahora q termine en ;
    int len_resto = strlen(resto) - 1;
    while(len_resto >= 0 && isspace(resto[len_resto])){
        len_resto--;
    }
    if(len_resto < 0 || resto[len_resto]!= ';'){
        return 0;
    }
    return 1;
}

int verificasion_PuntoYComa(char* definicion){
    int indice=0;
    while(definicion[indice]!='\0' && definicion[indice]!=';'){
        indice++;
    }
    if(definicion[indice]=='\0'){
        //recorrimos todo y no encontramos ; MAL
        return 0;
    }
    int pos_de_PyC=indice;
    indice++;//nos movemos a la siguente
    while(definicion[indice]!='\0' && definicion[indice]==' '){
        indice++;
    }
    if(definicion[indice]=='\0'){
        definicion[pos_de_PyC]='\0';
        //llegamos al final, despues del ; hay solo espacios esta bien
        return 1;
    }
    //despues del ; habia otro caracter mal
    return 0;
}

int isPrimitiva(char* nombre_fun){
    if(strcmp(nombre_fun,"0i")==0 ||strcmp(nombre_fun,"0d")==0||strcmp(nombre_fun,"Si")==0||strcmp(nombre_fun,"Sd")==0||strcmp(nombre_fun,"Di")==0 ||strcmp(nombre_fun,"Dd")==0){
        return 1;
    }
    return 0;
}



int isValidoFun(char* definicion,TablaHash* Tabla_de_funiones){
    char copy[4096];
    char token[4096];
    strcpy(copy,definicion);
    int indice=0;
    int flag=1;
    int fin=strlen(copy);
    //sacamos espacios ineserios
    while(fin> 0 && isspace((unsigned char)copy[fin - 1])){
        fin--;
    }
    //verificamos q este el ;
    if(fin > 0 && copy[fin-1]==';'){
        fin--;
    }
    //lo sacamos
    copy[fin] = '\0';
    
    while(copy[indice]!='\0' && flag){
        if(isspace(copy[indice])){
            indice++;
        }
        else if(copy[indice]=='<'){
            int j = indice + 1;
            // para indicar que encontramos un < definimos nivel, si encontramos un > lo bajamos, si es un < sube
            int nivel = 1;
            while (copy[j]!='\0' && nivel > 0){
                if (copy[j] == '<'){ 
                    //encontramos un <, sube
                    nivel++;
                }
                else if (copy[j] == '>'){
                    //ahora un > bajamos
                    nivel--;
                }
                j++;
            }
            if (nivel != 0) {
                //falto cerrar un >
                flag=0;
            }
            else{ 
                char subexpr[4096];
                strncpy(subexpr, copy + indice + 1, j - indice - 2);//copiamos la subexpresion dentro del < >
                subexpr[j - indice - 2] = '\0';

                if (!isValidoFun(subexpr, Tabla_de_funiones)){ 
                    flag=0;
                }
                else{
                    // nos paramos ahora despues de validar el < ..f..>
                    indice = j; 
                }
            }
        }
        else{
            //analisamos SUBCOAMNDO
            int pos=0;
            while(copy[indice]!='\0'  && !isspace(copy[indice]) && copy[indice] != '<' && copy[indice] != '>'){
                token[pos] = copy[indice];
                pos++; 
                indice++;
            }
            token[pos] = '\0';
            
            if (pos > 0){ 
                if (!isPrimitiva(token) && buscar(Tabla_de_funiones, token) == NULL){ 
                    flag = 0; 
                } 
            }
        }
    }
    //tambien lo sacamos de la palabra
    definicion[fin]='\0';
    return flag;
}


TablaHash* funcion_deff(char* Comando,TablaHash* Tabla_de_funciones){
    Comando=strtok(NULL," =");
    if(buscar(Tabla_de_funciones,Comando)!=NULL){
        printf("FUNCION ya definida\n");
        return Tabla_de_funciones;
    }
    if(isPrimitiva(Comando)){
        //esto es para no definir una funcion con el nombre de una primitiva nomas
        printf("Nombre invalido\n");
        return Tabla_de_funciones;
    }
    char nombre_Fun[64];
    strcpy(nombre_Fun,Comando);//guardamos el nombre
    Comando=strtok(NULL,"=");
    char definicion[1024];
    strcpy(definicion,Comando);
    if(isValidoFun(definicion,Tabla_de_funciones)){

        printf("FUNCION GUARDADA!\n");
        insertar(&Tabla_de_funciones,nombre_Fun,definicion);
        return Tabla_de_funciones;
    }
    else{
        printf("No VALIDO\n");
        return Tabla_de_funciones;
    }
    
}

//DEFL-----------------------------------------------------

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


// FUNCION APLYYYYYYYYYYYYYYYYYYYYY-----------------------------


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