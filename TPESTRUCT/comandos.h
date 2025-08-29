#ifndef __COMANDOS_H__
#define __COMANDOS_H__

#include"hash.h"
#include<string.h>
#include<stdio.h>
#include<ctype.h>

/*
Funcion deff: es la funcion que trabaja cuando recibe un comando que empieza con deff
recibe lo ingresado por teclado separado por el strtok y la tabla de funciones
Revisa el nombre de la funcion, si se encuentra en la tabla de funciones
no hace nada pues no se puede sobreescribir funciones, caso contrario
mientras leemos las funciones q estan despues = revisamos q sea primitivo,una 
funcion perteneciente a la tabla de funciones o si es de la forma <f> con f siendo
primitiva o es de la tabla de funciones. Si esta todo bien ahi agrega la funcion definida
en la tabla junto con el string que va despues del =.
Una vez finalizado devuelve la tabla 
*/
TablaHash* funcion_deff(char* Comando,TablaHash* Tabla_de_funciones);

/*
Funcion que verifica que  se cumpla bien el ; osea que cuando haya ; luego solo puede haber una sucesion de " "
donde obviamente termine con '\0', si luego del ; hay un caracter que no sea " " o '\0' se considera q esta mal
tambien verifica que este si este no esta se considera que no se ingreso bien el comando
*/
int verificasion_PuntoYComa(char* definicion);

/*
Verifica que la funcion sea una primitiva
si es devuelve 1 sino un 0
*/
int isPrimitiva(char* nombre_fun);



/*
Funcion que verifica que lo q hay despues del = sea valido
si es valido devuelve 1 sino 0
el checkeo de punto y coma esta porq cuando hay <f> verifica q f sea valida
y como f no tiene q terminar con ; no hay q hacer ese checeo entonces ponemos
0 si hay q ver el pinto y coma(dentro de la funcion)
1 si hay q ver q termine con punto y coma(primera llamda)
*/
int isValidoFun(char* definicion,TablaHash* Tabla_de_funiones,int check_puntoYComa);

/*
Revisa q el char sea los caracteres del '0' al '9', https://elcodigoascii.com.ar/codigos-ascii/numero-nueve-9-codigo-ascii-57.html
*/
int isNumber(char fragmento);

/*
Verifica que la definicion de lista sea valida
osea que termine con ; se habra y se cierre []
adentro haya numeros, desp de eso "," y otro numero
y todo lo q se pide
*/
int isValidoLis(char* definicion,int validar_puntoYComa);

/*
Funcon que se encarga de definir listas verifica q no haya otra ya definida
luego si puede, revisa q la definicion sea valida
*/
TablaHash* funcion_defl(char* Comando,TablaHash* Tabla_de_listas);

#endif

