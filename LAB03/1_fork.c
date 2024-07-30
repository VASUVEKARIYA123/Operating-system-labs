#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
// fork
int main(){
    printf("Before fork\n");
    int i =1;
    // create a new process by duplicating the calling process
    fork();
    fork();
    // fork();

    //         p
    //     c1     c2
    //  c11   

    //so after fork all statment run twise by two different process
    // printf("After fork %d \n",i);


    if(fork()==0){
        i = i +1;
        printf("After fork %d %lld\n",i,&i);

    }
    else{
        i = i +2;
        printf("After fork %d %lld\n",i,&i);
    }
    return 0;
}