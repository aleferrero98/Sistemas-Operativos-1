#include "main.h"
#include "redirection.h"
#include "program.h"

void redireccionar(char **argv){

	pid_t child_pid;
    int error, child_status;
    child_pid = fork ();//duplica el proceso

	if(child_pid == 0){

    int i,out=0;
    char output[64];

    for(i=0;argv[i] != NULL;i++)
    {
     
        if(strcmp(argv[i],">")==0)
        {      
            argv[i]=NULL;
            strcpy(output,argv[i+1]);
            printf("output echo: %s",output);
            out=2;
        }         
    }

    if(out)
    {

        int fd1;
        if ((fd1 = creat(output , 0644)) < 0) {
            perror("Couldn't open the output file");
            exit(0);
        }           

        dup2(fd1, STDOUT_FILENO); 
        close(fd1);
    }

    execvp(*argv, argv);
    perror("execvp");
    _exit(1);

     
	}
	 else if((child_pid) < 0)
    {     
        printf("fork() failed!\n");
        exit(1);
    }

    else {                                 

        error=waitpid(child_pid, &child_status, 0);
        if(error==-1) perror("Error al esperar proceso hijo\n");
    
	}
}