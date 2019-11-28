#include "main.h"
#include "commands.h"
#include "program.h"
#include "redirection.h"

void actuar(char *comando){
    char *aux;
    eliminarEspacios(comando);//me saca todos los espacios del comienzo

    if(strncmp(comando,"cd ",3) == 0){
        aux = strtok(comando," ");//me busca todo lo que sigue al comando
        aux = strtok(NULL," \n");//el proximo caracter puede ser espacio o \n
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
        int background = FALSE;
        char *argList[10];
        background = separarPalabras(comando,argList);
        ejecutarPrograma(argList,background);
    }
}
/*
Separa el argumento string palabra por palabra en un arreglo de strings
Retorna true si el proceso debe ejecutarse en segundo plano (ultimo string = &)
*/
int separarPalabras(char *linea, char *buffer[]){
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
    
    if(strcmp(buffer[i-1],"&")==0){//verifica si el ultimo elemento ingresado como comando es el &
        buffer[i-1]=NULL;//reemplaza el ultimo elemento & por null
        return TRUE;
    }else{
        buffer[i]=NULL;//ultimo elemento del arreglo debe ser nulo
        return FALSE;
    } 
    
}
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
    if((strstr(linea,"<") != NULL) || (strstr(linea,">") != NULL)){
        char *arg[10];
        checkEspacios(linea);
        char aux[256] = "echo ";
        strcat(aux,linea);
        separarPalabras(aux,arg);
        redireccionar(arg);   
    }
    else{ printf("cagamos%s", linea);}
}

void checkEspacios(char *line){
    for(int i = 0; line[i] != '\n'; i++){
        if(line[i] == '>'){
            if((line[i-1] != ' ') ||(line[i+1] != ' ')){
                char buffer[100] = "";
                strncat(buffer,line,i);
                strcat(buffer, " > ");
                strcat(buffer, strstr(line, ">")+1);
                printf("buf: %s en i= %d\n",buffer,i);
                strcpy(line, buffer);
            }
        }
    }
}