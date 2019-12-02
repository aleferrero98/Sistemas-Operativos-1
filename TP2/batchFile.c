#include "main.h"
#include "batchFile.h"
#include "commands.h"
#include "prompt.h"

void leerBatchfile(char *archivo){//lee archivo desde el path que se le pasa
    //printf("Archivo: %s\n",archivo);
    FILE *fp;
    fp = fopen(archivo,"r");
    if (fp==NULL) {//verifica que no haya error
        fputs ("File error",stderr);
        exit (1);
    }
    while(!feof(fp)){
        char buffer[256];
        fgets(buffer,256,fp);
        if(strcmp(buffer,"\n")==0){
            continue;
        }
        prompt();
        if(checkIO(buffer) || strstr(buffer,"cd")!=NULL){
            printf("\n");
        }
        if(checkIO(buffer) && strstr(buffer,"echo") == NULL){
            //printf("el buffer:%s\n",buffer );
            redir(buffer,1);
        }else actuar(buffer);
    }
    fclose(fp);
    exit(0);//finaliza la ejecucion
    return;
}