#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<semaphore.h>
#include<pthread.h>

sem_t mutex;
long long int cnt = 0;
// also in lab4-4_learn

void* fun1(){
    
    for(int i = 1; i <= 500000; i++){
        sem_wait(&mutex);
        cnt++;
        printf("%lld\n",cnt);
        sem_post(&mutex);
    }
    
    return NULL;
}


int main(){
    sem_init(&mutex,0,1);
    
    pthread_t t[5];
    for(int i = 0 ; i < 5 ; i++){
         pthread_create(&t[i],NULL,fun1,NULL); 
    }
    for(int i = 0 ; i < 5 ; i++){
        pthread_join(t[i],NULL);
    }
    
    printf("cnt : %lld\n",cnt);
    return 0;
}