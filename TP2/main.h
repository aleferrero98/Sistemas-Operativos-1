#ifndef _MAIN_H_
#define _MAIN_H_
//se definen todas las bibliotecas comunes a todos los archivos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>//contiene funciones para el manejo de archivos y directorios
#include <fcntl.h> //file control options
#include <sys/types.h>//contiene funciones de busqueda y ordenamiento de directorios y manipulacion de archivos
#include <sys/wait.h>

int isEmpty(char linea[]);
int checkIO(char linea[]);

#endif //_MAIN_H_