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
    printf("pipe created\n");
    printf("%d - %d\n",fd[0],fd[1]);
        
    return 0;
}