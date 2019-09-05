#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>

void imprimirDatos(FILE *archivo);
//void buscarDato(char *dato, FILE* archivo);
void printDatosCPU(void);
void printFormato(char* label, long time);
void printFechaHora(char* tipo);
void printTiempoActivo(void);
//void cambiosContexto(void);
//void cantidadProcesos(void);
void buscarDatoSinTitulo(char *dato, FILE* archivo, char caracterDeCorte);
void tiempoCPU(void);
void leerArchivo(char *ruta, char *presentacion);
void leerLineaArchivo(char *ruta, char *presentacion, char *datoAbuscar);
int peticionesDisco(void);
void promedioCarga1min(void);
void impresionPeriodica(char extras[3][10]);
int checkArgumentos(char *argv[]);

int main(int argc, char* argv[]) {
    int nextOption;
    const char* const shortOptions = "sl";

    if(checkArgumentos(argv)){
        printf("Error, argumentos no apropiados, solo puede usar un argumento por vez\n Los argumentos aceptados son -s, -l, -p, -f o -t\n");
        return 0;
    } 

    leerArchivo("/proc/sys/kernel/hostname", "Nombre de la máquina es: ");
    printFechaHora("fecha");
    printFechaHora("hora");
    printDatosCPU();

    leerArchivo("/proc/sys/kernel/osrelease", "Version del Kernel: ");
    printTiempoActivo();

    leerArchivo("/proc/filesystems", "Cantidad de file system soportados por el kernel:\n");

    char extras[3][10] = {" "," "," "};
    int exclucion = 0;   

    do{
        nextOption=getopt(argc,argv,shortOptions);
        switch(nextOption){
            case 'l':
                exclucion = 1;
                tiempoCPU();
                leerLineaArchivo("/proc/stat","Cantidad de cambios de contexto:","ctxt");
                leerLineaArchivo("/proc/stat","Cantidad de procesos abiertos desde inicio del sistema:", "processes");        
                for(int i = 0; optind < argc & i < 3; optind++, i++){      
                    strcpy(extras[i],argv[optind]);
                } 
                impresionPeriodica(extras);
                break;
            case 's':
                if(exclucion == 0){
                    tiempoCPU();
                    leerLineaArchivo("/proc/stat","Cantidad de cambios de contexto:","ctxt");
                    leerLineaArchivo("/proc/stat","Cantidad de procesos abiertos desde inicio del sistema:", "processes");
                }
                break;
            case -1:    //si no hay caracteres de opcion o si se llega al final de la lista de opciones, getOpt devuelve -1
                break;
            default:
                abort();
        }
    }while(nextOption != -1);

    return 0;
}

int checkArgumentos(char *argv[])
{
    if(argv[1] != NULL && argv[2] != NULL){
    if((strcmp(argv[1],"-l") == 0 || strcmp(argv[1],"-s") == 0) && (strcmp(argv[2],"-l") == 0 || strcmp(argv[2],"-s") == 0)) return 1;
    else return 0;
    }
    return 0;
}

void tiempoCPU(void){
    //IMPLEMENTAR
    return;
}
void leerArchivo(char *ruta, char *presentacion){
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
    buscarDatoSinTitulo("vendor_id", archivoCPU, ':');
    printf("%s", "Modelo de CPU");
    buscarDatoSinTitulo("model name", archivoCPU, ':');

    fclose(archivoCPU);
    return;
}
/*
void imprimirDatos(FILE *archivo){
    char buffer[100];

    fscanf(archivo, "%s" ,buffer);
    printf("%s \n", buffer);

}*/
void imprimirDatos(FILE *archivo){
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
void printFormato(char* label, long time){
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

    printFormato("Tiempo de actividad", (long) uptime);
    printFormato("Tiempo de inactividad", (long) idleTime);
}

void printFechaHora(char* tipo){
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

void leerLineaArchivo(char *ruta, char *presentacion, char *datoAbuscar){
    FILE *archivo;
    archivo = fopen(ruta,"r");
    printf("%s", presentacion);
    buscarDatoSinTitulo(datoAbuscar,archivo, ' ');
    fclose(archivo);

    return;
}
/*
void cambiosContexto(void){
    FILE *archivo;
    archivo = fopen("/proc/stat","r");
    printf("Cantidad de cambios de contexto:");
    buscarDatoSinTitulo("ctxt",archivo);
    fclose(archivo);

    return;
}

void cantidadProcesos(void){
    FILE *archivo;
    archivo = fopen("/proc/stat","r");
    printf("Cantidad de procesos abiertos desde inicio del sistema:");
    buscarDatoSinTitulo("processes",archivo);
    fclose(archivo);

    return;
}*/

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
}

int peticionesDisco(){
    FILE *archivo;
    archivo = fopen("/proc/diskstats","r");
    char datos[6][20];
    char buffer[200];
    char *aux;

    for(int i = 0; !feof(archivo); i++){
        fgets(buffer,200,archivo);
        aux = strstr(buffer,"sda ");
        if(aux != NULL){
            sscanf(aux,"%s %s %s %s %s %s",datos[0],datos[1],datos[2],datos[3],datos[4],datos[5]);
        }
    }
    return atoi(datos[1]) + atoi(datos[5]); 
    
    fclose(archivo);
}

void promedioCarga1min(void){
    FILE *archivo;
    archivo = fopen("/proc/loadavg","r");
    char buffer[5];
    fgets(buffer,5,archivo);
    printf("Promedio de carga en el ultimo minuto: %s\n",buffer);
}

void impresionPeriodica(char extras[3][10]){
    printf("Peticiones a disco: %d\n",peticionesDisco());
    leerLineaArchivo("/proc/meminfo","Cantidad de memoria configurada en hardware:","MemTotal:");
    leerLineaArchivo("/proc/meminfo","Cantidad de memoria disponible:", "MemAvailable:");            
    promedioCarga1min();

    if(strcmp(extras[0]," ") == 0 && strcmp(extras[1]," ") == 0)return;
    else if((strcmp(extras[2]," ") != 0) || (strcmp(extras[0], " ") != 0 && strcmp(extras[1]," ") == 0)){
        printf("Error, deben ingresarse 2 argumentos\n");
        return;
    }
    else{
        int limite = atoi(extras[1]);
        int intervalos = atoi(extras[0]);
        //printf("limite %d intervalos %d\n",limite,intervalos);
        for(int i = intervalos; i < limite; i += intervalos){ //i = intervalos porque la primera iteracion ya ocurrio
            sleep(intervalos);
            printf("\n");
            printf("Peticiones a disco: %d\n",peticionesDisco());
            leerLineaArchivo("/proc/meminfo","Cantidad de memoria configurada en hardware:","MemTotal:");
            leerLineaArchivo("/proc/meminfo","Cantidad de memoria disponible:", "MemAvailable:");
            promedioCarga1min();
            printf("Pausa de %d segundos\n", intervalos);
        }
    }
}