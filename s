[1mdiff --git a/TP1/rdproc/rdproc-v1 b/TP1/rdproc/rdproc-v1[m
[1mindex 8748883..59b263f 100755[m
Binary files a/TP1/rdproc/rdproc-v1 and b/TP1/rdproc/rdproc-v1 differ
[1mdiff --git a/TP1/rdproc/rdproc-v1.c b/TP1/rdproc/rdproc-v1.c[m
[1mindex d58b2fc..071e903 100644[m
[1m--- a/TP1/rdproc/rdproc-v1.c[m
[1m+++ b/TP1/rdproc/rdproc-v1.c[m
[36m@@ -14,10 +14,6 @@[m [mvoid printFechaHora(char* tipo);[m
 void printTiempoActivo(void);[m
 void printNombreMaquina(void);[m
 void printFileSystem(void);[m
[31m-void cambiosContexto(void);[m
[31m-void cantidadProcesos(void);[m
[31m-void buscarDatoSinTitulo(char *dato, FILE* archivo);[m
[31m-[m
 [m
 int main(int argc, char* argv[]) {[m
     printNombreMaquina();[m
[36m@@ -27,8 +23,6 @@[m [mint main(int argc, char* argv[]) {[m
     printDatosKernel();[m
     printTiempoActivo();[m
     printFileSystem();[m
[31m-    cambiosContexto();[m
[31m-    cantidadProcesos();[m
     [m
     return 0;[m
 }[m
[36m@@ -148,39 +142,3 @@[m [mvoid printFechaHora(char* tipo){[m
         printf("%s \n", "ERROR");[m
     }[m
 }[m
[31m-[m
[31m-void cambiosContexto(void){[m
[31m-    FILE *archivo;[m
[31m-    archivo = fopen("/proc/stat","r");[m
[31m-    printf("Cantidad de cambios de contexto:");[m
[31m-    buscarDatoSinTitulo("ctxt",archivo);[m
[31m-    fclose(archivo);[m
[31m-[m
[31m-    return;[m
[31m-}[m
[31m-[m
[31m-void cantidadProcesos(void){[m
[31m-    FILE *archivo;[m
[31m-    archivo = fopen("/proc/stat","r");[m
[31m-    printf("Cantidad de procesesos abiertos desde inicio del sistema:");[m
[31m-    buscarDatoSinTitulo("processes",archivo);[m
[31m-    fclose(archivo);[m
[31m-[m
[31m-    return;[m
[31m-}[m
[31m-[m
[31m-void buscarDatoSinTitulo(char *dato, FILE* archivo){//dato: es el string a buscar[m
[31m-    char buffer[100];[m
[31m-    int aux;[m
[31m-    while(!feof(archivo)){ //mientras no se llegue al final del archivo[m
[31m-        fgets(buffer,100,archivo); //Lee una linea del archivo[m
[31m-        aux=strncmp(dato, buffer, strlen(dato)); //compara los primeros n caracteres[m
[31m-        if(aux==0){[m
[31m-            char *c;[m
[31m-            c=strstr(buffer, " ");[m
[31m-            printf("%s", c);[m
[31m-            return;[m
[31m-        }[m
[31m-    }[m
[31m-    printf("%s", "No se encontró el dato especificado");[m
[31m-}[m
[1mdiff --git a/TP1/rdproc/rdproc-v1.o b/TP1/rdproc/rdproc-v1.o[m
[1mindex 1e51fc9..c7297ea 100644[m
Binary files a/TP1/rdproc/rdproc-v1.o and b/TP1/rdproc/rdproc-v1.o differ
[1mdiff --git a/TP1/rdproc/rdproc-v2.c b/TP1/rdproc/rdproc-v2.c[m
[1mindex 6f65cbf..44e4459 100644[m
[1m--- a/TP1/rdproc/rdproc-v2.c[m
[1m+++ b/TP1/rdproc/rdproc-v2.c[m
[36m@@ -14,6 +14,9 @@[m [mvoid printFechaHora(char* tipo);[m
 void printTiempoActivo(void);[m
 void printNombreMaquina(void);[m
 void printFileSystem(void);[m
[32m+[m[32mvoid cambiosContexto(void);[m
[32m+[m[32mvoid cantidadProcesos(void);[m
[32m+[m[32mvoid buscarDatoSinTitulo(char *dato, FILE* archivo);[m
 [m
 int main(int argc, char* argv[]) {[m
     printNombreMaquina();[m
[36m@@ -23,6 +26,8 @@[m [mint main(int argc, char* argv[]) {[m
     printDatosKernel();[m
     printTiempoActivo();[m
     printFileSystem();[m
[32m+[m[32m    cambiosContexto();[m
[32m+[m[32m    cantidadProcesos();[m
     [m
     return 0;[m
 }[m
[36m@@ -141,4 +146,40 @@[m [mvoid printFechaHora(char* tipo){[m
     }else{[m
         printf("%s \n", "ERROR");[m
     }[m
[31m-}[m
\ No newline at end of file[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32mvoid cambiosContexto(void){[m
[32m+[m[32m    FILE *archivo;[m
[32m+[m[32m    archivo = fopen("/proc/stat","r");[m
[32m+[m[32m    printf("Cantidad de cambios de contexto:");[m
[32m+[m[32m    buscarDatoSinTitulo("ctxt",archivo);[m
[32m+[m[32m    fclose(archivo);[m
[32m+[m
[32m+[m[32m    return;[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32mvoid cantidadProcesos(void){[m
[32m+[m[32m    FILE *archivo;[m
[32m+[m[32m    archivo = fopen("/proc/stat","r");[m
[32m+[m[32m    printf("Cantidad de procesesos abiertos desde inicio del sistema:");[m
[32m+[m[32m    buscarDatoSinTitulo("processes",archivo);[m
[32m+[m[32m    fclose(archivo);[m
[32m+[m
[32m+[m[32m    return;[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32mvoid buscarDatoSinTitulo(char *dato, FILE* archivo){//dato: es el string a buscar[m
[32m+[m[32m    char buffer[100];[m
[32m+[m[32m    int aux;[m
[32m+[m[32m    while(!feof(archivo)){ //mientras no se llegue al final del archivo[m
[32m+[m[32m        fgets(buffer,100,archivo); //Lee una linea del archivo[m
[32m+[m[32m        aux=strncmp(dato, buffer, strlen(dato)); //compara los primeros n caracteres[m
[32m+[m[32m        if(aux==0){[m
[32m+[m[32m            char *c;[m
[32m+[m[32m            c=strstr(buffer, " ");[m
[32m+[m[32m            printf("%s", c);[m
[32m+[m[32m            return;[m
[32m+[m[32m        }[m
[32m+[m[32m    }[m
[32m+[m[32m    printf("%s", "No se encontró el dato especificado");[m
[32m+[m[32m}[m
