//Step B: Command line arguments
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>

void imprimirDatos(FILE *archivo);
//void buscarDato(char *dato, FILE* archivo);
void printDatosCPU(void);
void printFormato(char* label, long time);
void printFechaHora(char* tipo);
void printTiempoActivo(void);
char* buscarDatoSinTitulo(char *dato, FILE* archivo, char caracterDeCorte);
void tiempoCPU(void);
void leerArchivo(char *ruta, char *presentacion);
void leerLineaArchivo(char *ruta, char *presentacion, char *datoAbuscar);

int main(int argc, char* argv[]) {
    int nextOption;
    const char* const shortOptions = "s";

    leerArchivo("/proc/sys/kernel/hostname", "Nombre de la máquina es: ");
    printFechaHora("fecha");
    printFechaHora("hora");
    printDatosCPU();

    leerArchivo("/proc/sys/kernel/osrelease", "Version del Kernel: ");
    printTiempoActivo();

    leerArchivo("/proc/filesystems", "Cantidad de file system soportados por el kernel:\n");
    

    do{
        nextOption=getopt(argc,argv,shortOptions);
        switch(nextOption){
            case 's':
                tiempoCPU();
                leerLineaArchivo("/proc/stat","Cantidad de cambios de contexto:","ctxt");
                leerLineaArchivo("/proc/stat","Numero de procesos creados desde inicio del sistema:", "processes");
                break;
            case -1:    //si no hay caracteres de opcion o si se llega al final de la lista de opciones, getOpt devuelve -1
                break;
            default:
                abort();
        }
    }while(nextOption != -1);
    
    return 0;
}

void tiempoCPU(void){
    char* linea;
    long int user, nice, system, idle;
    FILE *fp;
    fp = fopen ("/proc/stat","r");
    if (fp==NULL) {
        fputs ("File error",stderr);
        exit (1);
    }
	printf("%s","Cantidad de tiempo de CPU utilizado para:\n" );
	linea=buscarDatoSinTitulo("cpu",fp,' '); //me lee la linea que empieza con "cpu" y me devuelve lo que sigue
	sscanf(linea, "%ld %ld %ld %ld", &user, &nice, &system, &idle);// lu es unsigned long
	printf("%s %ld %s\n", "	Procesos normales en modo usuario:",user, "jiffies");
	printf("%s %ld %s\n","	Procesos niced en modo usuario:", nice, "jiffies");
	printf("%s %ld %s\n","	Sistema:", system, "jiffies");
	printf("%s %ld %s\n", "	Procesos idle:", idle, "jiffies");
    return;
}
char* buscarDatoSinTitulo(char *dato, FILE* archivo, char caracterDeCorte){//dato: es el string a buscar
    char buffer[100];
    int aux;
    while(!feof(archivo)){ //mientras no se llegue al final del archivo
        fgets(buffer,100,archivo); //Lee una linea del archivo
        aux=strncmp(dato, buffer, strlen(dato)); //compara los primeros n caracteres
        if(aux==0){
            char *c;
            c=strchr(buffer, caracterDeCorte);
            return c;
        }
    }
    printf("%s", "No se encontró el dato especificado");
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
void printDatosCPU(void){
    FILE *archivoCPU;
    archivoCPU = fopen ( "/proc/cpuinfo", "r" );
    if (archivoCPU==NULL) {
        fputs ("File error",stderr);
        exit (1);
    }
    printf("%s", "Información referida a la CPU:\n");
    printf("%s", "Tipo de CPU");
    printf("%s",buscarDatoSinTitulo("vendor_id", archivoCPU, ':'));
    printf("%s", "Modelo de CPU");
    printf("%s", buscarDatoSinTitulo("model name", archivoCPU, ':'));

    fclose(archivoCPU);
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
/*
void buscarDato(char *dato, FILE* archivo){//dato: es el string a buscar
    char buffer[100];
    int aux;
    while(!feof(archivo)){ //mientras no se llegue al final del archivo
        fgets(buffer,100,archivo); //Lee una linea del archivo
        aux=strncmp(dato, buffer, strlen(dato)); //compara los primeros n caracteres
        if(aux==0){
            printf("%s", buffer);
            return;
        }
    }
    printf("%s", "No se encontró el dato especificado");
}*/
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
    FILE *archivo;
    char aux[100];
    archivo = fopen(ruta,"r");
    printf("%s", presentacion);
    printf("%s", buscarDatoSinTitulo(datoAbuscar,archivo, ' '));//imprime la linea
    fclose(archivo);

    return;
}
/*
void buscarDatoSinTitulo(char *dato, FILE* archivo, char caracterDeCorte){//dato: es el string a buscar
    char buffer[100];
    int aux;
    while(!feof(archivo)){ //mientras no se llegue al final del archivo
        fgets(buffer,100,archivo); //Lee una linea del archivo
        aux=strncmp(dato, buffer, strlen(dato)); //compara los primeros n caracteres
        if(aux==0){
            char *c;
            //c=strstr(buffer, " ");
            //c=strchr(buffer, ' ');
            c=strchr(buffer, caracterDeCorte);
            printf("%s", c);
            return;
        }
    }
    printf("%s", "No se encontró el dato especificado");
}*/

