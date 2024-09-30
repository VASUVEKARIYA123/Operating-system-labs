#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
    char *a[] ={"ls","-l",NULL};
    execv("/bin/ls",a);
     
    return 0;
}