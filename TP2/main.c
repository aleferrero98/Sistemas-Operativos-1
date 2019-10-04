#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>//contiene funciones para el manejo de archivos y directorios
#include <sys/types.h>//contiene funciones de busqueda y ordenamiento de directorios y manipulacion de archivos
#define clrscr() printf("\e[1;1H\e[2J") //definimos un macro para limpiar la pantalla

void prompt(void);
void leerArchivo(char *ruta, char *buffer);
void realizarAccion(char *comando);
void actuar(char *comando);

int main(int argc, char *argv[]){
    char comandos[100]="";
    
    while(1){
        prompt();
        //scanf("%c", comandos);
        //scanf("%s", comandos); //no toma bien toda la linea
        fgets(comandos,100,stdin);
        //realizarAccion(comandos);
        actuar(comandos);
        strcpy(comandos, "");
    }

    return 0;
}

void prompt(void){//nombreUsuario@nombreMaquina:~$
    char buffer[100]="";
    //system("echo $USER > /tmp/nombreUsuario.txt");//no se si esta bien usar esto
    system("whoami > /tmp/nombreUsuario.txt");//crea txt como un archivo temporal

    char username[20]="";

    leerArchivo("/tmp/nombreUsuario.txt",username);
    
    strcat(buffer,username);
    strcat(buffer,"@");
    leerArchivo("/proc/sys/kernel/hostname", buffer);
    strcat(buffer,":~");
    //cwd
    char cwd[256];
    if(getcwd(cwd,sizeof(cwd))==NULL) perror("getcwd() error");
    strcat(buffer,strstr(cwd,username)+strlen(strtok(username," ")));
    strcat(buffer,"$ ");
    printf("%s", buffer);
}
void leerArchivo(char *ruta, char *buffer){//abre el archivo de la ruta indicada y te devuelve el contenido
    FILE *fp;
    char texto[100];
    fp = fopen (ruta,"r");
    if (fp==NULL) {//si hay error al abrir...
        fputs ("File error",stderr);
        exit (1);
    }
    while(!feof(fp)){ 
        fscanf(fp, "%s" ,texto);//copia el contenido en variable auxiliar
    }
    strcat(buffer, texto);//concatena al final
    fclose(fp);
}

void actuar(char *comando){
    char *aux;
    printf("completo %s",comando);
    aux = strtok(comando," ");
    aux = strtok(NULL,"\n");
    printf("primera parte %s a\n", comando);
    printf("segunda parte %s a\n", aux);

    if(strstr(comando,"cd") != NULL){
        if(chdir(aux)) perror("chdri() error"); 
    }
    if(strstr(comando,"clr")){
        clrscr();
    }
    if(strstr(comando,"quit")){
        exit(0);
    }
}


/*
void realizarAccion(char *comando){
int next_option;
    const char* const short_options = "";
    const struct option long_option[] = {
            {"cd",optional_argument,NULL,0},
            {"ls", optional_argument,NULL,0},
            {"exit", no_argument,NULL,0},
            {NULL,0,NULL,0}
    };

    do{
        next_option=getopt_long_only(argc, argv, "", long_option, NULL);//solo parametros largos    
        switch(next_option){
            case 'cd':
                printf("cd");
                break;
            case 'ls':
                
                break;
            case 'exit':
                exit(0);//termina el programa
                break;
            case -1:  //si no hay caracteres de opcion o si se llega al final de la lista de opciones, getOpt devuelve -1
                break;
            case '?':
                fprintf (stderr, "La opción -%c requiere un argumento.\n", optopt);
                abort();
                break;
            default:
                abort();//si no hubo parametros ni un -1 entonces hay un error
        }
    }while(next_option != -1);
}
