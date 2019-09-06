#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stepA.h"

void tiempoCPU(void);
void leerLineaArchivo(char *ruta, char *presentacion, char *datoAbuscar);

void leerLineaArchivo(char *ruta, char *presentacion, char *datoAbuscar){//lee una linea especifica de un archivo
    char aux[100];
    printf("%s", presentacion);
    printf("%s", buscarDatoSinTitulo(datoAbuscar,ruta, ' '));//imprime la linea

    return;
}

void tiempoCPU(void){
    char* linea;
    long int user, nice, system, idle;
    printf("%s","Cantidad de tiempo de CPU utilizado para:\n" );
    linea=buscarDatoSinTitulo("cpu","/proc/stat",' '); //me lee la linea que empieza con "cpu" y me devuelve lo que sigue
    sscanf(linea, "%ld %ld %ld %ld", &user, &nice, &system, &idle);// lu es unsigned long
    printf("%s %ld %s\n","  ->Procesos normales en modo usuario:",user, "jiffies");
    printf("%s %ld %s\n","  ->Procesos niced en modo usuario:", nice, "jiffies");
    printf("%s %ld %s\n","  ->Sistema:", system, "jiffies");
    printf("%s %ld %s\n","  ->Procesos idle:", idle, "jiffies");
    return;
}