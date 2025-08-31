#include"deff.h"

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
