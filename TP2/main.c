
#include "main.h"
#include "prompt.h"
#include "commands.h"
#include "batchFile.h"


int main(int argc, char *argv[]){
    char comandos[100]="";
    
    if(argv[1] == NULL){
        while(1){
            prompt();
            fgets(comandos,100,stdin);
            if(!isEmpty(comandos) && comandos[0]!='\n'){
                if(checkIO(comandos) && strstr(comandos,"echo") == NULL){
                    pid_t child_pid;
                    int error, child_status;
                    child_pid = fork ();//duplica el proceso

                    if(child_pid == 0){

                    int fd0,fd1,i,in=0,out=0;
                    char input[64],output[64];
                    char *prog;
                    prog = argv[0];


                    for(i=0;comandos[i] != '\n';i++)
                    {
                        if(comandos[i] == '<')
                        {        
                            char *aux;
                            aux = strstr(comandos, "<") + 1;
                            eliminarEspacios(aux);
                            printf("aux es %s\n",aux);
                       //     printf("aux: %s",aux);            
                            strcpy(input,aux);
                            strtok(input, " ");
                            printf("input:%s\n",input);
                            prog = strtok(comandos,"<");
                            strtok(prog," ");
                            printf("%s\n",prog);
                            comandos[i]='\0';
                         //   strcpy(input,comandos[i+1]);
                            in=2;           
                        }               

                        if(comandos[i] == '>')
                        {      
                            //comandos[i]=NULL;
                            char *aux;
                            aux = strstr(comandos, ">") + 1;
                            eliminarEspacios(aux);
                         //   printf("aux: %s",aux);            
                            strcpy(output, aux);
                            strtok(output, " ");
                            printf("output:%s\n",output);
                            prog = strtok(comandos,"<");
                            strtok(prog," ");
                            printf("%s\n",prog);
                            comandos[i]='\0';
                            //strcpy(output,comandos[i+1]);
                            out=2;
                        }         
                    }

                    //si el char '<' se encontro en string
                    if(in)
                    {   

                        int fd0;
                        if ((fd0 = open(input, O_RDONLY, 0)) < 0) {
                            perror("No se pudo abrir input file");
                            exit(0);
                        }           
                        dup2(fd0, STDIN_FILENO); 

                        close(fd0); 
                    }

                    if (out)
                    {

                        int fd1 ;
                        if ((fd1 = creat(output , 0644)) < 0) {
                            perror("No se pudo abrir output file");
                            exit(0);
                        }           

                        dup2(fd1, STDOUT_FILENO); 
                        close(fd1);
                    }

                    //execvp(*argv, argv);
                    execvp(prog,argv);
                    perror("execvp");
                    //_exit(1);
                    abort();
                     
                    }
                     else if((child_pid) < 0)
                    {     
                        printf("fork() fallo!\n");
                        exit(1);
                    }

                    else {                                  /* para el padre:      */

                        error=waitpid(child_pid, &child_status, 0);
                        if(error==-1) perror("Error al esperar proceso hijo\n");
                    
                    }
                }
                else actuar(comandos);
            }
            strcpy(comandos, "");
        }
    }else{
        char file[256];
        for(int i = 1; i < argc; i++){
            strcat(file,argv[i]);
            if(argv[i+1] != NULL) strcat(file," ");
        }
        leerBatchfile(file);
        actuar("quit");
    }

    return 0;
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
/*
void realizarAccion(char *comando){
int next_option;
    const char* const short_options = "";
    const struct option long_option[] = {
            {"cd",optional_argument,NULL,0},
            {"ls", optional_argument,NULL,0},
            {"exit", no_argument,NULL,0},
            {NULL,0,NULL,0}
    };

    do{
        next_option=getopt_long_only(argc, argv, "", long_option, NULL);//solo parametros largos    
        switch(next_option){
            case 'cd':
                printf("cd");
                break;
            case 'ls':
                
                break;
            case 'exit':
                exit(0);//termina el programa
                break;
            case -1:  //si no hay caracteres de opcion o si se llega al final de la lista de opciones, getOpt devuelve -1
                break;
            case '?':
                fprintf (stderr, "La opción -%c requiere un argumento.\n", optopt);
                abort();
                break;
            default:
                abort();//si no hubo parametros ni un -1 entonces hay un error
        }
    }while(next_option != -1);
}
*/