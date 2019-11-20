#include "main.h"
#include "redirection.h"
#include "program.h"

void redireccionar(char **argv){

    // funcion para redireccion ( '<' , '>' )

	pid_t child_pid;
    int error, child_status;
    child_pid = fork ();//duplica el proceso

	if(child_pid == 0){

    int fd0,fd1,i,in=0,out=0;
    char input[64],output[64];

    // finds where '<' or '>' occurs and make that argv[i] = NULL , to ensure that command wont't read that

    for(i=0;argv[i] != NULL;i++)
    {
        /*if(strcmp(argv[i],"<")==0)
        {        
            argv[i]=NULL;
            strcpy(input,argv[i+1]);
            in=2;           
        }    */           

        if(strcmp(argv[i],">")==0)
        {      
            argv[i]=NULL;
            strcpy(output,argv[i+1]);
            out=2;
        }         
    }

    //if '<' char was found in string inputted by user
   /* if(in)
    {   

        // fdo is file-descriptor
        int fd0;
        if ((fd0 = open(input, O_RDONLY, 0)) < 0) {
            perror("Couldn't open input file");
            exit(0);
        }           
        // dup2() copies content of fdo in input of preceeding file
        dup2(fd0, STDIN_FILENO); 

        close(fd0); 
    }*/

    //if '>' char was found in string inputted by user 
    if (out)
    {

        int fd1 ;
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

    // otra syntaxis
    /*      if (!(execvp(*argv, argv) >= 0)) {     // execute the command  
            printf("*** ERROR: exec failed\n");
            exit(1);
     */ 
	}
	 else if((child_pid) < 0)
    {     
        printf("fork() failed!\n");
        exit(1);
    }

    else {                                  /* for the parent:      */

        error=waitpid(child_pid, &child_status, 0);
        if(error==-1) perror("Error al esperar proceso hijo\n");
    
	}
}