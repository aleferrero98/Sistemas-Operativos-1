//Step D: Process
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void imprimirDatos(FILE *archivo);
void printDatosCPU(void);
void printFormato(char* label, long time);
void printFechaHora(char* tipo);
void printTiempoActivo(void);
char* buscarDatoSinTitulo(char *dato, char *path, char caracterDeCorte);
void tiempoCPU(void);
void leerArchivo(char *ruta, char *presentacion);
void leerLineaArchivo(char *ruta, char *presentacion, char *datoAbuscar);


int main(int argc, char* argv[]) {
    int nextOption;
    const char* const shortOptions = "st:p:f:";//: indica que necesita si o si parametros, :: los parametros son opcionales

    leerArchivo("/proc/sys/kernel/hostname", "Nombre de la máquina es: ");
    printFechaHora("fecha");
    printFechaHora("hora");
    printDatosCPU();
    leerArchivo("/proc/sys/kernel/osrelease", "Version del Kernel: ");
    printTiempoActivo();
    leerArchivo("/proc/filesystems", "Cantidad de file system soportados por el kernel:\n");
    

    do{
        nextOption=getopt(argc,argv,shortOptions);
        char buffer[50]="";
        switch(nextOption){
            case 's':
                tiempoCPU();
                leerLineaArchivo("/proc/stat","Cantidad de cambios de contexto:","ctxt");
                leerLineaArchivo("/proc/stat","Numero de procesos creados desde inicio del sistema:", "processes");
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

void tiempoCPU(void){
    char* linea;
    long int user, nice, system, idle;
    printf("%s","Cantidad de tiempo de CPU utilizado para:\n" );
    linea=buscarDatoSinTitulo("cpu","/proc/stat",' '); //me lee la linea que empieza con "cpu" y me devuelve lo que sigue
    sscanf(linea, "%ld %ld %ld %ld", &user, &nice, &system, &idle);// lu es unsigned long
    printf("%s %ld %s\n","  ->Procesos normales en modo usuario:",user, "jiffies");
    printf("%s %ld %s\n","  ->Procesos niced en modo usuario:", nice, "jiffies");
    printf("%s %ld %s\n","  ->Sistema:", system, "jiffies");
    printf("%s %ld %s\n","  ->Procesos idle:", idle, "jiffies");
    return;
}

char* buscarDatoSinTitulo(char *dato, char *path, char caracterDeCorte){//dato: es el string a buscar
    FILE *fp;
    fp = fopen (path,"r");
    if (fp==NULL) {
        fputs ("File error",stderr);
        exit (1);
    }
    char buffer[100]="";
    char *punt;
    int aux;
    while(!feof(fp)){ //mientras no se llegue al final del archivo
        fgets(buffer,100,fp); //Lee una linea del archivo
        aux=strncmp(dato, buffer, strlen(dato)); //compara los primeros n caracteres
        if(aux==0){
            /*
            char *c;
            c=strchr(buffer, caracterDeCorte);
            fclose(fp);
            return c;*/

            fclose(fp);
            punt=buffer;//puntero al primer elemento
            return punt+strlen(dato);
        }
    }
    fprintf(stderr,"No se encontró el dato especificado");
    fclose(fp);
    return '\0';

}

void leerArchivo(char *ruta, char *presentacion){//lee el archivo completo
    FILE *fp;
    fp = fopen (ruta,"r");
    if (fp==NULL) {
        fputs ("File error",stderr);
        exit (1);
    }
    printf("%s",presentacion);
    imprimirDatos(fp);
    fclose(fp);
}
void printDatosCPU(void){//imprime dos datos de /proc/cpuinfo
    
    printf("%s", "Información referida a la CPU:\n");
    printf("%s", "Tipo de CPU");
    printf("%s",buscarDatoSinTitulo("vendor_id", "/proc/cpuinfo", ':'));
    printf("%s", "Modelo de CPU");
    printf("%s", buscarDatoSinTitulo("model name", "/proc/cpuinfo", ':'));

    return;
}
/*
void imprimirDatos(FILE *archivo){
    char buffer[100];

    fscanf(archivo, "%s" ,buffer);
    printf("%s \n", buffer);

}*/
void imprimirDatos(FILE *archivo){//imprime todo el archivo
    char caracter;
    while((caracter = fgetc(archivo)) != EOF){
        printf("%c",caracter);
    }
}

void printFormato(char* label, long time){//cambia al formato hh:mm:ss.
    //Conversion de variables
    const long minute = 60;
    const long hour = minute * 60;
    const long day = hour * 24;
    
    printf ("%s: %ld dias, %ld:%02ld:%02ld\n", label, time / day,(time % day) / hour, (time % hour) / minute, time % minute);
}

void printTiempoActivo(void){
    FILE* fp;
    double uptime, idleTime;
/* Read the system uptime and accumulated idle time from /proc/uptime.*/
    fp = fopen ("/proc/uptime", "r");
    fscanf (fp, "%lf %lf\n", &uptime, &idleTime);
    fclose (fp);

    printFormato("Tiempo transcurrido desde que se inició el sistema operativo", (long) uptime);
    printFormato("Tiempo de inactividad", (long) idleTime);
}

void printFechaHora(char* tipo){//imprime la fecha u hora actual
    time_t t;
    struct tm *tm;
    char fechayhora[100];

    t=time(NULL);
    tm=localtime(&t);
    if(strcmp(tipo,"fecha")==0) {
        strftime(fechayhora, 100, "%d/%m/%Y", tm);
        printf("%s", "La fecha es: ");
        printf("%s \n", fechayhora);
    }else if(strcmp(tipo, "hora")==0){
        strftime(fechayhora, 100, "%H:%M:%S", tm);
        printf("%s", "La hora es: ");
        printf("%s \n", fechayhora);
    }else{
        printf("%s \n", "ERROR");
    }
}

void leerLineaArchivo(char *ruta, char *presentacion, char *datoAbuscar){//lee una linea especifica de un archivo
    char aux[100];
    printf("%s", presentacion);
    printf("%s", buscarDatoSinTitulo(datoAbuscar,ruta, ' '));//imprime la linea

    return;
}
