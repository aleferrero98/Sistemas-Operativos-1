#ifndef _COMMANDS_H_
#define _COMMANDS_H_
//define todo lo necesario

#define clrscr() printf("\e[1;1H\e[2J") //definimos un macro para limpiar la pantalla
void actuar(char *comando);
void echo(char *linea);
void eliminarEspacios(char *linea);
void separarPalabras(char *linea, char *buffer[]);

#endif //_COMMANDS_H_