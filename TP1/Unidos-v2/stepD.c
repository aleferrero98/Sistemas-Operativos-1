#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void infoFileDescriptors(char *path){

	FILE *fp;
	char buffer[1000]="";
    fp = fopen (path,"r");
    if(fp==NULL) {
        fputs ("File error",stderr);
        exit (1);
    }

	int i=0;
	char fdpermisos[8],type[15],name[100];
	printf("fd-permisos 		Tipo  		 Path al fd\n");
	while(!feof(fp)){ 
		fgets(buffer,1000,fp);
		if(i>0){
			sscanf(buffer,"%*s %*s %*s %7s %14s %*s %*s %*s %99s",fdpermisos,type,name);
			printf("%s 			 %s 		 %s\n",fdpermisos,type,name);
		}
		i++;
	}
	fclose(fp);
}