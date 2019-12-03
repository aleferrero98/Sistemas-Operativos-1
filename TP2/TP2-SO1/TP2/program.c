#include "main.h"
#include "program.h"

void ejecutarPrograma(char *arg[], int background){
    crearProceso(arg[0], arg, background);//arg[0] es el nombre del programa
    return;
}

void crearProceso(char* programa, char** argList, int background){
    pid_t child_pid;
    int error, child_status;
    child_pid = fork ();//duplica el proceso

    if (child_pid != 0){//true->proceso padre
        if(!background){//si el nuevo proceso se ejecuta en primer plano -> proceso padre debe esperar
            error=waitpid(child_pid, &child_status, 0);
            if(error==-1) perror("Error al esperar proceso hijo\n");
        }else{
            return;//nuevo proceso se ejecuta en segundo plano -> vuelve al prompt
        }
             
    }else {
        execvp(programa, argList);//proceso hijo
        fprintf (stderr, "Error ocurrido en execvp\n");//la funcion execvp retorna solo si ocurre un error
        abort ();
    }
}