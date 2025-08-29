#include"comandos.h"


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



int isValidoFun(char* definicion,TablaHash* Tabla_de_funiones,int check_puntoYComa){
    char copy[4096];
    char token[4096];
    strcpy(copy,definicion);
    if(check_puntoYComa==1){
        if(!verificasion_PuntoYComa(copy)){
            return 0;
        }
    }   
    int indice=0;
    int flag=1;
    while(copy[indice]!='\0' && flag){
        if(copy[indice]==' '){
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

            if (!isValidoFun(subexpr, Tabla_de_funiones,0)){ 
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
            while(copy[indice]!='\0' && copy[indice]!=' ' && copy[indice] != '<' && copy[indice] != '>'){
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
    if(flag==0){
        return 0;
    }
    return 1;
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
    if(isValidoFun(definicion,Tabla_de_funciones,1)){
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

int isValidoLis(char* definicion,int validar_puntoYComa){
    if(validar_puntoYComa){
    if(!verificasion_PuntoYComa(definicion)){
        return 0;
    }
    }
    int indice = 0;
    while(definicion[indice]==' '){
        indice++;
    }
    if(definicion[indice] != '['){
        // no empieza con [
        return 0; 
    }
    indice++;

    int valor_final = 1;
    int flag = 1;
    // controlamos que después de una coma venga un número

    while(definicion[indice] != '\0' && flag){
        while(definicion[indice] == ' '){
            indice++;
        }

        if(definicion[indice] == ']'){
            indice++;
            while(definicion[indice] == ' '){
                indice++;
            }
            if(definicion[indice] != '\0'){
                // basura después de ]
                valor_final = 0; 
            }
            flag = 0; 
        }
        else if(isNumber(definicion[indice])){
            while(isNumber(definicion[indice])){
                indice++;
            }
            while(definicion[indice] == ' '){
                indice++;
            }
            if(definicion[indice] == ','){
                indice++;
            }
        }
        else{
            valor_final = 0;
            flag = 0;
        }
    }
    return valor_final;
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
    if(!isValidoLis(definicion,1)){
        printf("definicion de lista invalida!!\n");
        return Tabla_de_listas;
    }
    printf("Lista Guardada!");
    insertar(&Tabla_de_listas,nombre_Lis,definicion);
    return Tabla_de_listas;
}


// FUNCION APLYYYYYYYYYYYYYYYYYYYYY-----------------------------


int isValidApply(char* definicion, TablaHash* tabla_de_funciones,TablaHash* tabla_de_listas){
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
            //acordarse de cambiar para q no busque el ;!!!!!!!!!!!!!!!!!!!!!!!
            if(isValidoLis(definicion+indice,0)){
                lista_valida=1;
            }
        }
        
    }
    else if(isalnum(definicion[indice])){
        int fin=indice;
        while(0<indice && definicion[indice]!=' '){
            indice--;
        }

        int inicio = indice+1;
        char nombre[128];
        strncpy(nombre, definicion+inicio, fin-inicio+1);
        nombre[fin-inicio+1]='\0';

        //buscamos ese nombre
        if(buscar(tabla_de_listas,nombre)!=NULL){
            lista_valida=1;
            //cortamos 
            definicion[inicio]='\0';
        }
    }
    if(!lista_valida){
        //Si no es valida la lista no revisamos ya la funcion
        return lista_valida;//osea 0
    }
    //AHORA revisamos funciones

    //funcion q valida que sea un funcion
    return isValidoFun(definicion,tabla_de_funciones,0);
}