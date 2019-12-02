
#include "main.h"
#include "prompt.h"
#include "commands.h"
#include "batchFile.h"

char **pargv;

int main(int argc, char *argv[]){
    char comandos[100]="";
    pargv = argv;
    
    if(argv[1] == NULL){//si ./myshell no tiene argumentos, entonces pide comando de entrada por stdin
        while(1){
            prompt();
            fgets(comandos,100,stdin);
            if(!isEmpty(comandos) && comandos[0]!='\n'){
                if(checkIO(comandos) && strstr(comandos,"echo") == NULL){
                    redir(comandos,0);  
                }
                else actuar(comandos);//comandos sin redireccionamiento o con echo
            }
            strcpy(comandos, "");//limpia el buffer
        }
    }else{//lee los comandos directamente del archivo batchfile
        char file[256];
        for(int i = 1; i < argc; i++){
            strcat(file,argv[i]);
            if(argv[i+1] != NULL) strcat(file," ");
        }
        leerBatchfile(file);
    }

    return 0;
}

void redir(char *comandos, int entrada){
	pid_t child_pid;
    int error, child_status;
    child_pid = fork ();//duplica el proceso

    if(child_pid == 0){
        int i,in=0,out=0;
        char input[64],output[64];
        char *prog;
        prog = pargv[0];

        for(i=0;comandos[i] != '\n';i++)
        {
            if(comandos[i] == '<')
            {        
                char *aux;
                aux = strstr(comandos, "<") + 1;
                eliminarEspacios(aux);
                strcpy(input,aux);
                strtok(input, " ");
               // printf("input:%s\n",input);
                prog = strtok(comandos,"<");
                strtok(prog," ");
              //  printf("prog:%s\n",prog);
                comandos[i]='\0';
                in=2;           
            }               

            if(comandos[i] == '>')
            {      
                char *aux;
                aux = strstr(comandos, ">") + 1;
                eliminarEspacios(aux);
                strcpy(output, aux);
                strtok(output, " ");
              //  printf("output:%s\n",output);
                prog = strtok(comandos,"<");
                strtok(prog," ");
              //  printf("prog:%s\n",prog);
                comandos[i]='\0';
                out=2;
                }         
            }

            if(in)//si el char '<' se encontro en string
            {   
                int fd0;
                if ((fd0 = open(input, O_RDONLY, 0)) < 0) {
                    perror("No se pudo abrir input file");
                    exit(0);
                }           
                dup2(fd0, STDIN_FILENO); 
                close(fd0); 
            }

            if (out)//si el char '>' se encontro en string
            {

    	        int fd1 ;
 	            if ((fd1 = creat(output , 0644)) < 0) {
         	        perror("No se pudo abrir output file");
            	    exit(0);
                }           

                dup2(fd1, STDOUT_FILENO); 
                close(fd1);
            }

			if(entrada == 0){
            	execvp(prog,pargv);
                perror("execvp");
                abort();	
            }
            else{
	            execvp(prog,pargv+1);
	            perror("execvp");
	            abort();
            }
        }
        else if((child_pid) < 0)
        {     
            printf("fork() fallo!\n");
            exit(1);
        }else{   /* para el padre:      */

	        error=waitpid(child_pid, &child_status, 0);
    		if(error==-1) perror("Error al esperar proceso hijo\n");
                    
        }
}

int checkIO(char linea[]){
    for(int i = 0; i < strlen(linea); i++){
        if(linea[i] == '<') return 1;
        if(linea[i] == '>') return 1;
    }
    return 0;
}

int isEmpty(char linea[]){//verifica si la linea solo tiene espacios
    int i = 0;
    while(linea[i]!='\n'){
        if(linea[i]!=' '){
            return FALSE;//falso
        }
        i++;
    }
    return TRUE; //verdadero
}
