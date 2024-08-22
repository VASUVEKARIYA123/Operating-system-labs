#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>

// pipe() System call
// for IPC -(inter-process communication)

// - a pipe is a connection between two processes, such that the standard output from one process becomes the standard input of the other process.


int main(){

    int fd[2];
    int x,y ;
    // fd[0] for read end
    // fd[1] for write end

    // fd - 0 std in
    // fd - 1 std out
    // fd - 2 std error
    // now you get onward fd in your pipe fd
    
    int p = pipe(fd);
    if(p == -1){
        printf("error\n");
        exit(1);
    }
    // printf("pipe created\n");
    // printf("%d - %d\n",fd[0],fd[1]);

    int p_id = fork();
    if(p_id == -1){
        printf("error\n");
        exit(1);
    }
    else if(p_id == 0){
        // child process
        printf("child process :\n");
        close(fd[1]); // close the write end
        int r_byte = read(fd[0],&y,sizeof(y));
        printf("byte read : %d \ny : %d\n",r_byte,y);
        printf("child process ends\n");
    }
    else{
        // parent process
        printf("parent process :\n");
        close(fd[0]); // close the read end
        x = 167;
        write(fd[1],&x,sizeof(x)); // writes the x in fd[1]
        wait(NULL);
        printf("parent process ends\n");
    }
    
    

    
    
    return 0;
}