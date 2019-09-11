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
	char command[20],pid[8],user[15],fdpermisos[8],type[15],device[10],size[15],node[15],name[100];
	printf("fd-permisos 		Tipo  		 Path al fd\n");
	while(!feof(fp)){ 
		fgets(buffer,1000,fp);
		if(i>0){
			sscanf(buffer,"%s %s %s %s %s %s %s %s %s",command,pid,user,fdpermisos,type,device,size,node,name);
			printf("%s 			 %s 		 %s\n",fdpermisos,type,name);
		}
		i++;
	}
	fclose(fp);
}