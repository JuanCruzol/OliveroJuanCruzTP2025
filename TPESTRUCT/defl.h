#ifndef __DEFL_H__
#define __DEFL_H__


#include"deff.h"

/*
Verifica que la definicion de lista sea valida
se habra y se cierre []
adentro haya numeros, desp de eso "," y otro numero
y todo lo q se pide, se aceptan listas vacias
los otros arguemntos son para la recursion y sirven para que 
sepa que tiene q ir desp
*/
int Isvalidlis(char* definicion,int espero_coma,int espero_num,int indice,int list_vacia);

/*
Funcon que se encarga de definir listas verifica q no haya otra ya definida
luego si puede, revisa q la definicion sea valida
*/
TablaHash* funcion_defl(char* Comando,TablaHash* Tabla_de_listas);



#endif