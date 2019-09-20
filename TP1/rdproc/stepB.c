#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void buscarDatoSinTitulo(char *dato, char *path, char *contenido);

void leerLineaArchivo(char *ruta, char *presentacion, char *datoAbuscar){//lee una linea especifica de un archivo
    char aux[100];
    printf("%s", presentacion);
    buscarDatoSinTitulo(datoAbuscar,ruta, aux);
    printf("%s", aux);//imprime la linea

    return;
}

void tiempoCPU(void){
    char linea[100];
    long int user, nice, system, idle;
    printf("%s","Cantidad de tiempo de CPU utilizado para:\n" );
    buscarDatoSinTitulo("cpu","/proc/stat",linea); //me lee la linea que empieza con "cpu" y me devuelve lo que sigue
    sscanf(linea, "%ld %ld %ld %ld", &user, &nice, &system, &idle);// lu es unsigned long
    printf("%s %ld %s\n","  ->Procesos normales en modo usuario:",user, "jiffies");
    printf("%s %ld %s\n","  ->Procesos niced en modo usuario:", nice, "jiffies");
    printf("%s %ld %s\n","  ->Sistema:", system, "jiffies");
    printf("%s %ld %s\n","  ->Procesos idle:", idle, "jiffies");
    return;
}