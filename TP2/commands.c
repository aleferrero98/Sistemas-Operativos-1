#include "main.h"
#include "commands.h"
#include "program.h"

void actuar(char *comando){
    char *aux;
   // printf("comando %s\n",comando);
    eliminarEspacios(comando);//me saca todos los espacios del comienzo
    printf("comando %s",comando);

    //if(strstr(comando,"cd ") != NULL){
    if(strncmp(comando,"cd ",3) == 0){
        aux = strtok(comando," ");//me busca todo lo que sigue al comando
        aux = strtok(NULL," \n");//el proximo caracter puede ser espacio o \n
        //printf("aux %s",aux);
        if(chdir(aux)) perror("chdri() error"); 

    }else if(strncmp(comando,"clr ",4) == 0){
        clrscr();
    }else if(strncmp(comando,"echo ",5) == 0){
        aux = strtok(comando," ");
        aux = strtok(NULL,"\n");
        echo(aux);
    }else if(strncmp(comando,"quit ",5) == 0){
        printf("\n");
        exit(0);
    }else{//si no es ningun comando, entonces es un programa a ejecutar
        printf("comando 2 %s\n",comando);
        char *argList[10];
        separarPalabras(comando,argList);
        printf("argList %s\n",argList[0]);
        printf("argList %s\n",argList[1]);
        printf("argList %s\n",argList[2]);

        ejecutarPrograma(argList);
    }
}
void separarPalabras(char *linea, char *buffer[]){//separa el argumento string palabra por palabra en un arreglo de strings
    char delimitador[] = " \n";
    char *token = strtok(linea, delimitador);
    int i=0;
    if(token != NULL){
        while(token != NULL){
            // Sólo en la primera pasamos la cadena; en las siguientes pasamos NULL
            buffer[i]=token;
            
            printf("buffer es %s\n", buffer[i]);
            i++;
            token = strtok(NULL, delimitador);
        }
    }
    buffer[i]=NULL;//ultimo elemento del arreglo debe ser nulo
    printf("i es %d\n", i);
}
/*
void echo(char *linea){
    char buffer[256] = "";
    for(int i = 0, j = 0; i < strlen(linea); i++){
    if(linea[i] != ' '){
        char c[2];
        c[0] = linea[i];
        strcat(buffer,c);
        if((linea[i+1] == ' ' )) strcat(buffer," ");
    } 
  }
  printf("%s\n",buffer);
}*/
void eliminarEspacios(char *linea){//elimina todos los espacios y tabulaciones que pueda tener un string "linea"
    char delimitador[] = " \t\n";
    char buffer[100]="";
    char *token = strtok(linea, delimitador);
    if(token != NULL){
        while(token != NULL){
            // Sólo en la primera pasamos la cadena; en las siguientes pasamos NULL
            strcat(buffer,token);
            strcat(buffer," ");
    
            token = strtok(NULL, delimitador);
        }
    }
    strcat(buffer,"\n");
    strcpy(linea, buffer);//devuelvo resultado en el string que me pasaron
}
void echo(char *linea){
    eliminarEspacios(linea);
    printf("%s", linea);
}