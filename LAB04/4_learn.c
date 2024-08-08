#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>

// 4. WAP to demonstrate use of mutex for handling global variables.

long long int cnt = 0;
pthread_mutex_t lock;
void* fun1(){
    // function for thread 1
    
    for(int i = 1; i <= 500000; i++){
        // 1).
        // cnt++;
        // printf("%lld\n",cnt);

        // 2).
        //lock on critical section
        pthread_mutex_lock(&lock); 
        cnt++;
        printf("%lld\n",cnt);
        pthread_mutex_unlock(&lock);

    }
    
    return NULL;
}


int main(){

    pthread_t t1;
    pthread_create(&t1,NULL,fun1,NULL); 
    // pthread_join(t1,NULL);
    
    pthread_t t2;
    pthread_create(&t2,NULL,fun1,NULL); 
    // pthread_join(t2,NULL);
    
    
    pthread_t t3;
    pthread_create(&t3,NULL,fun1,NULL); 
    // pthread_join(t3,NULL);
    
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    
   printf("cnt : %lld\n",cnt);
   
    
    return 0;
}