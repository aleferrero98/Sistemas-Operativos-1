#ifndef _COMMANDS_H_
#define _COMMANDS_H_
//define todo lo necesario
#define clrscr() printf("\e[1;1H\e[2J") //definimos un macro para limpiar la pantalla
#define TRUE 1
#define FALSE 0

void actuar(char *comando);
void echo(char *linea);
void eliminarEspacios(char *linea);
int separarPalabras(char *linea, char *buffer[]);

#endif //_COMMANDS_H_