#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
    int pid = fork();
    if(pid==0){
        printf("child\n");
        char *a[] ={"pwd",NULL};
        execv("/bin/pwd",a);
    }
    else{
        wait(NULL);
        printf("parent\n");
        char *a[] ={"ls","-l",NULL};
        execv("/bin/ls",a);
    }
    return 0;
}