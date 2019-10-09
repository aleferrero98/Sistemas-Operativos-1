#include "main.h"
#include "batchFile.h"
#include "commands.h"
#include "prompt.h"

void leerBatchfile(char *archivo){
    printf("Archivo: %s\n",archivo);
    FILE *fp;
    fp = fopen(archivo,"r");
    if (fp==NULL) {
        fputs ("File error",stderr);
        exit (1);
    }
    while(!feof(fp)){
        char buffer[256];
        fgets(buffer,256,fp);
        prompt();
        actuar(buffer);
    }
    fclose(fp);
    return;
}