#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    int fd = open("test.txt",O_WRONLY | O_APPEND);
    // int fdin = open("input.txt",O_RDONLY);
    printf("Hello\n");
    // dup2(0,fdin);
    
    

    dup2(fd,1);
    
    printf("it will print in test.txt\n");
    return 0;
}