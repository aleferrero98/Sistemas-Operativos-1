//Step A: rdproc, version inicial
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>

void imprimirDatos(FILE *archivo);
void imprimirFechaHora(char* tipo);
void buscarDato(char *dato, FILE* archivo);
void printDatosCPU(void);
void printDatosKernel(void);
void print_time (char* label, long time);

int main(int argc, char* argv[]) {




    FILE* fp;
    double uptime, idle_time;
/* Read the system uptime and accumulated idle time from /proc/uptime.*/
fp = fopen ("/proc/uptime", "r");
fscanf (fp, "%lf %lf\n", &uptime, &idle_time);
fclose (fp);
/* Summarize it. */
    print_time ("uptime", (long) uptime);
    print_time ("idle time", (long) idle_time);



    return 0;
}
void printDatosKernel(void){
    FILE *archivoKernel;
    archivoKernel = fopen("/proc/sys/kernel/osrelease","r");
    printf("%s", "Version del Kernel: ");
    imprimirDatos(archivoKernel);
    printf("\n");
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
void imprimirDatos(FILE *archivo){
    char buffer[100];

    fscanf(archivo, "%s" ,buffer);
    printf("%s \n", buffer);

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
void print_time (char* label, long time){
    /* Conversion constants. */
    const long minute = 60;
    const long hour = minute * 60;
    const long day = hour * 24;
    /* Produce output. */
    printf ("%s: %ld days, %ld:%02ld:%02ld\n", label, time / day,(time % day) / hour, (time % hour) / minute, time % minute);
}
