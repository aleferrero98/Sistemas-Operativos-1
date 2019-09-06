#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>

void printDatosCPU(void);
void leerArchivo(char *ruta, char *presentacion);
void printFechaHora(char* tipo);
void printTiempoActivo(void);
void buscarDatoSinTitulo(char *contenedor, char *dato, char *path, char caracterDeCorte);
void imprimirDatos(FILE *archivo);
void printFormato(char* label, long time);

void printDatosCPU(void){//imprime dos datos de /proc/cpuinfo
    char *contenedor[50]="";
    printf("%s", "Información referida a la CPU:\n");
    printf("%s", "Tipo de CPU");
    buscarDatoSinTitulo(contenedor,"vendor_id", "/proc/cpuinfo", ':')
    printf("%s", contenedor);
    printf("%s", "Modelo de CPU");
    buscarDatoSinTitulo(contenedor,"model name", "/proc/cpuinfo", ':')
    printf("%s", contenedor);

    return;
}

void buscarDatoSinTitulo(char *contenedor, char *dato, char *path, char caracterDeCorte){//dato: es el string a buscar
    FILE *fp;
    fp = fopen (path,"r");
    if (fp==NULL) {
        fputs ("File error",stderr);
        exit (1);
    }
    char buffer[100]="";
    char *punt;
    int aux;
    while(!feof(fp)){ //mientras no se llegue al final del archivo
        fgets(buffer,100,fp); //Lee una linea del archivo
        aux=strncmp(dato, buffer, strlen(dato)); //compara los primeros n caracteres
        if(aux==0){
         	fclose(fp);
            punt=buffer;//puntero al primer elemento
            strcpy(contenedor,punt+strlen(dato));
            return;
        }
    }
    fprintf(stderr,"No se encontró el dato especificado");
    fclose(fp);

}

void leerArchivo(char *ruta, char *presentacion){//lee el archivo completo
    FILE *fp;
    fp = fopen (ruta,"r");
    if (fp==NULL) {
        fputs ("File error",stderr);
        exit (1);
    }
    printf("%s",presentacion);
    imprimirDatos(fp);
    fclose(fp);
}

void imprimirDatos(FILE *archivo){//imprime todo el archivo
    char caracter;
    while((caracter = fgetc(archivo)) != EOF){
        printf("%c",caracter);
    }
}

void printFormato(char* label, long time){//cambia al formato hh:mm:ss.
    //Conversion de variables
    const long minute = 60;
    const long hour = minute * 60;
    const long day = hour * 24;
    
    printf ("%s: %ld dias, %ld:%02ld:%02ld\n", label, time / day,(time % day) / hour, (time % hour) / minute, time % minute);
}

void printTiempoActivo(void){
    FILE* fp;
    double uptime, idleTime;
/* Read the system uptime and accumulated idle time from /proc/uptime.*/
    fp = fopen ("/proc/uptime", "r");
    fscanf (fp, "%lf %lf\n", &uptime, &idleTime);
    fclose (fp);

    printFormato("Tiempo transcurrido desde que se inició el sistema operativo", (long) uptime);
    printFormato("Tiempo de inactividad", (long) idleTime);
}

void printFechaHora(char* tipo){//imprime la fecha u hora actual
    time_t t;
    struct tm *tm;
    char fechayhora[100];

    t=time(NULL);
    tm=localtime(&t);
    if(strcmp(tipo,"fecha")==0) {
        strftime(fechayhora, 100, "%d/%m/%Y", tm);
        printf("%s", "La fecha es: ");
        printf("%s \n", fechayhora);
    }else if(strcmp(tipo, "hora")==0){
        strftime(fechayhora, 100, "%H:%M:%S", tm);
        printf("%s", "La hora es: ");
        printf("%s \n", fechayhora);
    }else{
        printf("%s \n", "ERROR");
    }
}