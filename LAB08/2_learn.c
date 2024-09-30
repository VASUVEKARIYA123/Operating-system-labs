#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<semaphore.h>
#include<pthread.h>

// 2). WAP to Implement solution for writers have priority problem.


sem_t x,y,z,rsem,wsem;
long long int readCount = 0;
long long int writeCount = 0;
long long int data = 0;
int Aid = 1;

void* reader(void *id){
    
    // for giving id
    int tid = *(int*)id;
    (*((int *)id))++;

    while (1)
    {   
        sleep(1);
        sem_wait(&z);
        sem_wait(&rsem);
        sem_wait(&x);
        readCount++;
        if(readCount == 1) sem_wait(&wsem);
        sem_post(&x);
        sem_post(&rsem);
        sem_post(&z);
        printf("Reader %d is reading data %lld\n",tid,data);

        sem_wait(&x);
        readCount--;
        if(readCount == 0) sem_post(&wsem);
        sem_post(&x);
        sleep(8);

    }
    return NULL;
}

void* writer(void *id){
    int tid = *(int*)id;
    (*((int *)id))++;
    while(1){
        sem_wait(&y);
        writeCount++;
        if(writeCount == 1) sem_wait(&rsem);
        sem_post(&y);
        sem_wait(&wsem);
        printf("writer %d is writting\n",tid);
        data++;
        sem_post(&wsem);
        sem_wait(&y);
        writeCount--;
        if(writeCount == 0) sem_post(&rsem);
        sem_post(&y);
        sleep(2);
    }
}

int main(){
    
    sem_init(&x,0,1);
    sem_init(&y,0,1);
    sem_init(&z,0,1);
    sem_init(&rsem,0,1);
    sem_init(&wsem,0,1);

    readCount = 0;
    writeCount = 0;
    data = 0;
    pthread_t t[6];

    int i = 0;
    pthread_create(&t[0],NULL,reader,(void *)&Aid);
    for(i = 1 ; i < 6 ; i++){
         pthread_create(&t[i],NULL,writer,(void *)&Aid); 
    }
   
    for(int i = 0 ; i < 6 ; i++){
        pthread_join(t[i],NULL);
    }
    
    return 0;
}