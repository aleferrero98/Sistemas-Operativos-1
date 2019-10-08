
#include "main.h"
#include "prompt.h"
#include "commands.h"


int main(int argc, char *argv[]){
    char comandos[100]="";
    
    while(1){
        prompt();
        //scanf("%c", comandos);
        //scanf("%s", comandos); //no toma bien toda la linea
        fgets(comandos,100,stdin);
        actuar(comandos);
        strcpy(comandos, "");
    }

    return 0;
}

/*
void realizarAccion(char *comando){
int next_option;
    const char* const short_options = "";
    const struct option long_option[] = {
            {"cd",optional_argument,NULL,0},
            {"ls", optional_argument,NULL,0},
            {"exit", no_argument,NULL,0},
            {NULL,0,NULL,0}
    };

    do{
        next_option=getopt_long_only(argc, argv, "", long_option, NULL);//solo parametros largos    
        switch(next_option){
            case 'cd':
                printf("cd");
                break;
            case 'ls':
                
                break;
            case 'exit':
                exit(0);//termina el programa
                break;
            case -1:  //si no hay caracteres de opcion o si se llega al final de la lista de opciones, getOpt devuelve -1
                break;
            case '?':
                fprintf (stderr, "La opción -%c requiere un argumento.\n", optopt);
                abort();
                break;
            default:
                abort();//si no hubo parametros ni un -1 entonces hay un error
        }
    }while(next_option != -1);
}
*/