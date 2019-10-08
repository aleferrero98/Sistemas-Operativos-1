#include "main.h"
#include "prompt.h"

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