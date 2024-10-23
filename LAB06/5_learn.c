#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>
#include<string.h>
#include <errno.h>
#include <fcntl.h>


// 4. WAP to pass file name from parent process to child process and the child process should display file contents.

int main(){

    int fd[2];
    int fd1[2];
    char buf[1000] ;


    int p = pipe(fd);
    if(p == -1){
        printf("error\n");
        // exit(1);
    }
    int p2 = pipe(fd1);
    if(p2 == -1){
        printf("error\n");
        // exit(1);
    }
    int p_id = fork();
    if(p_id == -1){
        printf("error\n");
        exit(1);
    }
    else if(p_id == 0){
        // child process
        printf("child process :\n");
        close(fd[1]); // close the write end

        char filename[1000];
        char buff[1000];
        int r_byte = read(fd[0],filename,sizeof(filename));
        printf("byte read : %d \nfile name : %s\n",r_byte,filename);

        int filed = open(filename,O_RDONLY|O_CREAT);
        printf("file dis : %d\n",filed);
        int readbyte = read(filed,buff,sizeof(buff));
        printf("byte read : %d\nbuff data : %s\n",readbyte,buff);

        close(filed);

        printf("child process ends\n");
    }
    else{
        // parent process
        printf("parent process :\n");
        close(fd[0]); // close the read end
        
        char* file_name = "2_learn.c";
        write(fd[1],file_name,(strlen(file_name)+1)*sizeof(char)); // writes the x in fd[1]
        wait(NULL);
        printf("parent process ends\n");
    }
    
    

    
    
    return 0;
}