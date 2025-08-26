#include<stdio.h>
#include<string.h>

int main(){
    char buff[1024];
    scanf(" %[^\n]",buff);
    char* Partes=strtok(buff," =");
    while(Partes!=NULL){
        printf("%s\n",Partes);
        Partes=strtok(NULL," =");
    }
    return 0;
}