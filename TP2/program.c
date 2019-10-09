#include "main.h"
#include "program.h"

void ejecutarPrograma(char *arg[]){
    crearProceso(arg[0], arg);//arg[0] es el nombre del programa
    return;
}

void crearProceso(char* programa, char** argList){
    pid_t child_pid;
  
    child_pid = fork ();//duplica el proceso

    if (child_pid != 0)
        return;//proceso padre
    else {
        execvp(programa, argList);//proceso hijo
        fprintf (stderr, "Error ocurrido en execvp\n");//la funcion execvp retorna solo si ocurre un error
        abort ();
    }
}