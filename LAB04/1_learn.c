#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>

// pthread_create 
// pthread_join

void* fun1(){
    // function for thread 1
    printf("hello inside thread 1\n");
}

void* fun2(){
    //function for thread 2
    printf("hello inside thread 2\n");
}

int main(){

    

    //it was like thread pointer
    pthread_t t1;
    // we use it to create a thread
    pthread_create(&t1,NULL,fun1,NULL); 

    pthread_t t2;
    pthread_create(&t2,NULL,fun2,NULL);

    // if we join t1 and t2 thread then main process is wait for thread 1 and 2 to terminate 
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    printf("inside main  \n");
    
    return 0;
}