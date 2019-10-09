#ifndef _PROGRAM_H_
#define _PROGRAM_H_
//define todo lo necesario
#include <sys/types.h>//contiene funciones de busqueda y ordenamiento de directorios y manipulacion de archivos

void crearProceso(char* programa, char** argList);
void ejecutarPrograma(char *arg[]);

#endif //_PROGRAM_H_