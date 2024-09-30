#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<semaphore.h>
#include<pthread.h>

// 1). WAP to Implement solution for readers have priority problem.
    // - 5 reader thread
    // - 1 writer thread

sem_t x,wsem;
long long int readCount = 0;
long long int data = 0;
int Aid = 1;

void* reader(void *id){
    int tid = *(int*)id;
    // tid = pthread_self();
    (*((int *)id))++;
    while (1)
    {   
        sleep(1);
        sem_wait(&x);
        readCount++;
        if(readCount == 1) sem_wait(&wsem);
        sem_post(&x);
        long long int d = data;
        printf("ID : %d ,reading data %lld\n",tid,d);
        sem_wait(&x);
        readCount--;
        if(readCount == 0) sem_post(&wsem);
        sem_post(&x);
        sleep(2);
    }
    return NULL;
}

void* writer(void *id){
    int tid = *(int*)id;
    (*((int *)id))++;
    while(1){
        sem_wait(&wsem);
        printf("id : %d ,writing\n",tid);
        data++;
        sem_post(&wsem);
        sleep(10);
    }
}

int main(){
    sem_init(&x,0,1);
    sem_init(&wsem,0,1);
    readCount = 0;
    data = 0;
    pthread_t t[6];
    int i=0;
    pthread_create(&t[0],NULL,writer,(void *)&Aid);
    for(i = 1 ; i < 6 ; i++){
         pthread_create(&t[i],NULL,reader,(void *)&Aid); 
    }
   
    for(int i = 0 ; i < 6 ; i++){
        pthread_join(t[i],NULL);
    }
    
    
    return 0;
}