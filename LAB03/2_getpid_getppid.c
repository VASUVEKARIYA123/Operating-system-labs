#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
// getpid, getppid
int main(){
    printf("Before fork\n");
    int i = 0;
    // swapper is the first process to start after the kernel is loaded.(PID = 0)
    // init is parent of all Linux processes with PID or process ID of 1
    // fork return pid of child to parent and 0 to child on success and -1 on fail
    if(fork()==0){
        printf("this block is executed in child process only\n");
        printf("p : %d\n",getpid());
        printf("pp : %d\n",getppid());
        
    }
    else{
        printf("this block is executed in parent process only\n");
        printf("p : %d\n",getpid());
        printf("pp : %d\n",getppid());
    }
        
    }
    else{
        printf("this block is executed in parent process only\n");
        printf("p : %d\n",getpid());
        printf("pp : %d\n",getppid());
    }
    

    return 0;
}