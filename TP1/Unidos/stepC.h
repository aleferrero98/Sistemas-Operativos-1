#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>
#include "stepB.h"

int peticionesDisco(void);
void promedioCarga1min(void);
void impresionPeriodica(char extras[3][10]);
int checkArgumentos(char *argv[]);

int checkArgumentos(char *argv[])
{
    if(argv[1] != NULL && argv[2] != NULL){
    if((strcmp(argv[1],"-l") == 0 || strcmp(argv[1],"-s") == 0) && (strcmp(argv[2],"-l") == 0 || strcmp(argv[2],"-s") == 0)) return 1;
    else return 0;
    }
    return 0;
}

int peticionesDisco(){
    FILE *archivo;
    archivo = fopen("/proc/diskstats","r");
    char datos[6][20];
    char buffer[200];
    char *aux;

    for(int i = 0; !feof(archivo); i++){
        fgets(buffer,200,archivo);
        aux = strstr(buffer,"sda ");
        if(aux != NULL){
            sscanf(aux,"%s %s %s %s %s %s",datos[0],datos[1],datos[2],datos[3],datos[4],datos[5]);
        }
    }
    return atoi(datos[1]) + atoi(datos[5]); 
    
    fclose(archivo);
}

void promedioCarga1min(void){
    FILE *archivo;
    archivo = fopen("/proc/loadavg","r");
    char buffer[5];
    fgets(buffer,5,archivo);
    printf("Promedio de carga en el ultimo minuto: %s\n",buffer);
}

void impresionPeriodica(char extras[3][10]){
   /* printf("Peticiones a disco: %d\n",peticionesDisco());
    leerLineaArchivo("/proc/meminfo","Cantidad de memoria configurada en hardware:","MemTotal:");
    leerLineaArchivo("/proc/meminfo","Cantidad de memoria disponible:", "MemAvailable:");            
    promedioCarga1min();*/

    if((strcmp(extras[0]," ") == 0 && strcmp(extras[1]," ") == 0) ||((strcmp(extras[2]," ") != 0) || (strcmp(extras[0], " ") != 0 && strcmp(extras[1]," ") == 0))){
    	printf("Error, deben ingresarse 2 argumentos\n");
    	return;
    }
    else{
        int limite = atoi(extras[1]);
        int intervalos = atoi(extras[0]);
        //printf("limite %d intervalos %d\n",limite,intervalos);
        for(int i = 0; i < limite; i += intervalos){ //i = intervalos porque la primera iteracion ya ocurrio
            sleep(intervalos);
            printf("\n");
            printf("Peticiones a disco: %d\n",peticionesDisco());
            leerLineaArchivo("/proc/meminfo","Cantidad de memoria configurada en hardware:","MemTotal:");
            leerLineaArchivo("/proc/meminfo","Cantidad de memoria disponible:", "MemAvailable:");
            promedioCarga1min();
            printf("Pausa de %d segundos\n", intervalos);
        }
    }
}