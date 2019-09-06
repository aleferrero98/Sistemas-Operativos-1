#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "stepC.h"

int main(int argc, char* argv[]) {
    int nextOption;
    const char* const shortOptions = "slt:p:f:";//: indica que necesita si o si parametros, :: los parametros son opcionales

    if(checkArgumentos(argc,argv)){
        fprintf(stderr,"Error, argumentos no apropiados, solo puede usar un argumento por vez\n Los argumentos aceptados son -s, -l, -p, -f o -t\n");
        return 1;
    }

    leerArchivo("/proc/sys/kernel/hostname", "Nombre de la máquina es: ");
    printFechaHora("fecha");
    printFechaHora("hora");
    printDatosCPU();
    leerArchivo("/proc/sys/kernel/osrelease", "Version del Kernel: ");
    printTiempoActivo();
    leerArchivo("/proc/filesystems", "Cantidad de file system soportados por el kernel:\n");
    
    char extras[3][10] = {" "," "," "};

    do{
        nextOption=getopt(argc,argv,shortOptions);
        char buffer[50]="";
        switch(nextOption){
            case 's':
                tiempoCPU();
                leerLineaArchivo("/proc/stat","Cantidad de cambios de contexto:","ctxt");
                leerLineaArchivo("/proc/stat","Numero de procesos creados desde inicio del sistema:", "processes");
                break;
            case 'l':
                tiempoCPU();
                leerLineaArchivo("/proc/stat","Cantidad de cambios de contexto:","ctxt");
                leerLineaArchivo("/proc/stat","Cantidad de procesos abiertos desde inicio del sistema:", "processes");        
                for(int i = 0; optind < argc & i < 3; optind++, i++){      
                    strcpy(extras[i],argv[optind]);
                } 
                impresionPeriodica(extras);
                break;
            
            case 't':
                tiempoCPU();
                leerLineaArchivo("/proc/stat","Cantidad de cambios de contexto:","ctxt");
                leerLineaArchivo("/proc/stat","Numero de procesos creados desde inicio del sistema:", "processes");

                strcpy(buffer,""); //limpio el contenido del buffer
                strcat(buffer, "sudo cat /proc/");
                strcat(buffer, optarg);//optarg es el argumento para esta opcion
                strcat(buffer, "/stack");
                printf("%s\n",buffer);
                system(buffer); 

                break;
            case 'p':
                tiempoCPU();
                leerLineaArchivo("/proc/stat","Cantidad de cambios de contexto:","ctxt");
                leerLineaArchivo("/proc/stat","Numero de procesos creados desde inicio del sistema:", "processes");

                strcpy(buffer,""); //limpio el contenido del buffer
                strcat(buffer,"lsof -a -p ");
                strcat(buffer,optarg);
                /*strcat(buffer, "ls -l /proc/");
                strcat(buffer, optarg);//optarg es el argumento para esta opcion
                //strcat(buffer, "/fd > fileDescriptors.txt");//guarda los datos en un txt para despues leer lo que necesita      
                strcat(buffer, "/fd");*/
                printf("%s\n",buffer);
                system(buffer); 
                break;
            case 'f':
                strcpy(buffer,""); //limpio el contenido del buffer
                strcat(buffer, "/proc/");
                strcat(buffer, optarg);
                strcat(buffer, "/limits");
                char mensaje[80]="Los limites de archivos abiertos para el proceso ";
                strcat(mensaje,optarg);
                strcat(mensaje," son:");
                printf("%s\n", mensaje);
                strcpy(mensaje,buscarDatoSinTitulo("Max open files", buffer, ' '));//copio la linea leida
                long int soft, hard;

                sscanf(mensaje, "%ld %ld", &soft, &hard);
                printf("%s %ld %s\n","  ->Limite de software:",soft, "archivos");
                printf("%s %ld %s\n","  ->Limite de hardware:", hard, "archivos");

                break;
            case -1:    //si no hay caracteres de opcion o si se llega al final de la lista de opciones, getOpt devuelve -1
                break;
            case '?':
                fprintf (stderr, "La opción -%c requiere un argumento.\n", optopt);
            default:
                abort();//si no hubo parametros ni un -1 entonces hay un error
        }
    }while(nextOption != -1);
    
    return 0;
}
