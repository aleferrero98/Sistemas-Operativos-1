#include "main.h"
#include "batchFile.h"
#include "commands.h"
#include "prompt.h"

void leerBatchfile(char *archivo){//lee archivo desde el path que se le pasa
    printf("Archivo: %s\n",archivo);
    FILE *fp;
    fp = fopen(archivo,"r");
    if (fp==NULL) {//verifica que no haya error
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