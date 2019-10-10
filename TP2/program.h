#ifndef _PROGRAM_H_
#define _PROGRAM_H_
//define todo lo necesario
#include <sys/types.h>//contiene funciones de busqueda y ordenamiento de directorios y manipulacion de archivos
#include <sys/wait.h>
void crearProceso(char* programa, char** argList, int background);
void ejecutarPrograma(char *arg[], int background);

#endif //_PROGRAM_H_