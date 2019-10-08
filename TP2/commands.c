#include "main.h"
#include "commands.h"

void actuar(char *comando){
    char *aux;
    printf("completo %s",comando);
    aux = strtok(comando," ");
    aux = strtok(NULL,"\n");
    printf("primera parte %s a\n", comando);
    printf("segunda parte %s a\n", aux);

    if(strstr(comando,"cd") != NULL){
        if(chdir(aux)) perror("chdri() error"); 
    }else if(strstr(comando,"clr")){
        clrscr();
    }else if(strstr(comando,"echo")){
        echo(aux);
    }else if(strstr(comando,"quit")){
        exit(0);
    }
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

void echo(char *linea){

    char delimitador[] = " \t";
    char *token = strtok(linea, delimitador);
    if(token != NULL){
        while(token != NULL){
            // Sólo en la primera pasamos la cadena; en las siguientes pasamos NULL
            printf("%s", token);
            printf("%c", ' ');
            token = strtok(NULL, delimitador);
        }
    }
    printf("%c", '\n');
}