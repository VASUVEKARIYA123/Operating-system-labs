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


    int p = pipe(fd);
    if(p == -1){
        printf("error\n");
        exit(1);
    }
    int p2 = pipe(fd1);
    if(p2 == -1){
        printf("error\n");
        exit(1);
    }
   
    int p_id = fork();
    if(p_id == -1){
        printf("error3\n");
        exit(1);
    }
    else if(p_id == 0){
        // child process
        printf("child process :\n");
        close(fd[1]); // close the write end p to c
        close(fd1[0]); // close the read end of c to p

        char filename[1000];
        char buff[1000];
        int r_byte = read(fd[0],filename,sizeof(filename));
        printf("byte read : %d \nfile name : %s\n",r_byte,filename);

        // open the file and read data from file
        int filed = open(filename,O_RDONLY|O_CREAT);
        printf("file dis : %d\n",filed);

        int readbyte ;
        // while(readbyte = read(filed,buff,sizeof(buff)) > 0 ){

        // //send content of file to parent through pip2
            
        // }
        int writebyte = write(fd1[1],buff,readbyte);
            // printf("byte written in child : %d\n",writebyte);
        close(filed);
        close(fd[0]); 
        close(fd1[1]); 
        printf("child process ends\n");
    }
    else{
        // parent process
        printf("parent process :\n");
        close(fd[0]); // close the read end
        close(fd1[1]); // close the write end
        
        char* file_name = "text.txt";
        write(fd[1],file_name,strlen(file_name)+1); // writes the x in fd[1]
        wait(NULL);
        //get content from child process through pip2
        char buff[1000];
        int readbyte = read(fd1[0],buff,sizeof(buff));
        printf("byte read in parent : %d\n",readbyte);
        printf("content of file : %s\n",buff);
        
        printf("parent process ends\n");
    }
    
    

    
    
    return 0;
}