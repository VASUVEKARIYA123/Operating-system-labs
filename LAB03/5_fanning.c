#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
// fanning

int main(){
    int n = 4;

    // printf("Before fork\n");

    for(int i = 0 ; i < n ; i++){
        int t = fork();
        if(t<0){
            printf("Error\n");
            return -1;
        }
        else if(t==0){
            printf("Child %d %d %d \n",i,getpid(),getppid());
            return 0;
        }
    }
    
    return 0;
}