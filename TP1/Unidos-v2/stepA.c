#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>

void buscarDatoSinTitulo(char *dato, char *path, char *contenido);
void imprimirDatos(FILE *archivo);
void printFormato(char* label, long time);

void printDatosCPU(void){//imprime dos datos de /proc/cpuinfo
    char aux[100];
    printf("%s", "Información referida a la CPU:\n");
    printf("%s", "Tipo de CPU");
    buscarDatoSinTitulo("vendor_id", "/proc/cpuinfo", aux);
    printf("%s", aux);
    printf("%s", "Modelo de CPU");
    buscarDatoSinTitulo("model name", "/proc/cpuinfo", aux);
    printf("%s", aux);

    return;
}

void buscarDatoSinTitulo(char *dato, char *path, char *contenido){//dato: es el string a buscar
    FILE *fp;
    fp = fopen (path,"r");
    if (fp==NULL) {
        fputs ("File error",stderr);
        exit (1);
    }
    char buffer[100]="";
    char *aux;
    while(!feof(fp)){ //mientras no se llegue al final del archivo
        fgets(buffer,100,fp); //Lee una linea del archivo
        aux=strstr(buffer, dato);
        if(aux!=NULL){
         	fclose(fp);
            strcpy(contenido, (aux+strlen(dato)));//copia los datos siguientes a la palabra clave en el buffer de parametro de la funcion
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
    while(!feof(archivo)){
        printf("%c",fgetc(archivo));
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
    fp = fopen ("/proc/uptime", "r");
    fscanf (fp, "%lf %lf\n", &uptime, &idleTime);
    fclose (fp);

    printFormato("Tiempo transcurrido desde que se inició el sistema operativo", (long) uptime);
    printFormato("Tiempo de inactividad", (long) idleTime);
}

void printFecha(void){//imprime la fecha actual
    time_t t;
    struct tm newFecha;
    char fecha[100];
    t=time(NULL);
    localtime_r(&t,&newFecha);
    strftime(fecha, 100, "%d/%m/%Y", &newFecha);
    printf("%s", "La fecha es: ");
    printf("%s \n", fecha);
    
}

void printHora(void){//imprime la hora actual
    time_t t;
    struct tm newhora;
    char hora[100];
    t=time(NULL);
    localtime_r(&t,&newhora);
    strftime(hora, 100, "%H:%M:%S", &newhora);
    printf("%s", "La hora es: ");
    printf("%s \n", hora);
}