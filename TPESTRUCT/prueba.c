#include<stdio.h>
#include<string.h>
#include<stdlib.h>



int main(){
    char buff[1024];
    scanf(" %[^\n]",buff);
    
    printf("%d\n",atoi(buff));
    
    return 0;
}