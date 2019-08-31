//Step B: Command line arguments
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>

void imprimirDatos(FILE *archivo);
void buscarDato(char *dato, FILE* archivo);
void printDatosCPU(void);
void printDatosKernel(void);
void printFormato(char* label, long time);
void printFechaHora(char* tipo);
void printTiempoActivo(void);
void printNombreMaquina(void);
void printFileSystem(void);

int main(int argc, char* argv[]) {
    printNombreMaquina();
    printFechaHora("fecha");
    printFechaHora("hora");
    printDatosCPU();
    printDatosKernel();
    printTiempoActivo();
    printFileSystem();
    
    return 0;
}
void printFileSystem(void){
    FILE *filesystem;
    filesystem = fopen ( "/proc/filesystems", "r" );
    if (filesystem==NULL) {
        fputs ("File error",stderr);
        exit (1);
    }
    printf("%s","Cantidad de file system soportados por el kernel:\n");
    imprimirDatos(filesystem);
    fclose(filesystem);
}
void printNombreMaquina(void){
    FILE *archivoNombre;
    archivoNombre = fopen ( "/proc/sys/kernel/hostname", "r" );
    if (archivoNombre==NULL) {
        fputs ("File error",stderr);
        exit (1);
    }
    printf("%s","Nombre de la máquina es: ");
    imprimirDatos(archivoNombre);
    fclose(archivoNombre);
}
void printDatosKernel(void){
    FILE *archivoKernel;
    archivoKernel = fopen("/proc/sys/kernel/osrelease","r");
    printf("%s", "Version del Kernel: ");
    imprimirDatos(archivoKernel);
    if (archivoKernel==NULL) {
        fputs ("File error",stderr);
        exit (1);
    }

    fclose(archivoKernel);
}
void printDatosCPU(void){
    FILE *archivoCPU;
    archivoCPU = fopen ( "/proc/cpuinfo", "r" );
    if (archivoCPU==NULL) {
        fputs ("File error",stderr);
        exit (1);
    }
    printf("%s", "Información referida a la CPU:\n");
    buscarDato("vendor_id", archivoCPU);
    buscarDato("model name", archivoCPU);

    fclose(archivoCPU);
    return;
}
/*
void imprimirDatos(FILE *archivo){
    char buffer[100];

    fscanf(archivo, "%s" ,buffer);
    printf("%s \n", buffer);

}*/
void imprimirDatos(FILE *archivo){
    char caracter;
    while((caracter = fgetc(archivo)) != EOF){
        printf("%c",caracter);
    }
}

void buscarDato(char *dato, FILE* archivo){//dato: es el string a buscar
    char buffer[100];
    int aux;
    while(!feof(archivo)){ //mientras no se llegue al final del archivo
        fgets(buffer,100,archivo); //Lee una linea del archivo
        aux=strncmp(dato, buffer, strlen(dato)); //compara los primeros n caracteres
        if(aux==0){
            printf("%s", buffer);
            return;
        }
    }
    printf("%s", "No se encontró el dato especificado");
}
void printFormato(char* label, long time){
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

    printFormato("Tiempo de actividad", (long) uptime);
    printFormato("Tiempo de inactividad", (long) idleTime);
}

void printFechaHora(char* tipo){
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