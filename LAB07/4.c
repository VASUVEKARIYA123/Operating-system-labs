#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>


int main()
{
    int fd[2];
    pipe(fd);

    int pid = fork();
    if(pid == 0){
        close(fd[0]);
        dup2(fd[1],1);
        char *a[] ={"ls","-l",NULL};
        execv("/bin/ls",a);
    }
    else if(pid > 0){
        wait(NULL);
        close(fd[1]);
        dup2(fd[0],0);
        // char *a[] ={"sort",NULL};
        // execv("/bin/sort",a);

        char *a[] ={"wc",NULL};
        execv("/bin/wc",a);
    }

    return 0;
}