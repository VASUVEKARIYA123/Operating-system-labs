#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>

// 4. WAP to demonstrate use of mutex for handling global variables.

long long int cnt = 0;
pthread_mutex_t lock;

void* fun1(void* d){
    struct matrixpair* p = (struct matrixpair*)d;
    int* row1 = p->mat1;
    int* row2 = p->mat2;
    
    for(int i = 0; i<5 ;i++){
        row1[i] += row2[i];
    }
    
    return NULL;
}
struct matrixpair{
    int* mat1;
    int* mat2;
};

int main(){
    int arr1[][5] = {{1,1,1,1,1},{2,2,2,2,2},{3,3,3,3,3},{1,2,3,4,5}};
    int arr2[][5] = {{1,1,1,1,1},{2,2,2,2,2},{3,3,3,3,3},{1,2,3,4,5}};

    struct matrixpair m;
    m.mat1 = arr1;
    m.mat2 = arr2;

    for(int i = 0 ; i < 5; i++){
        struct matrixpair m;
        m.mat1 = arr1[i];
        m.mat2 = arr2[i];
        pthread_t t1;
        pthread_create(&t1,NULL,fun1,&m); 
        pthread_join(t1,NULL);
    }
    
    for(int i = 0 ; i < 5; i++){
        for(int j = 0 ; j < 5; j++){
            printf("%d ",arr1[i][j]);
        }
    }
    
    
   printf("cnt : %lld\n",cnt);
   
    
    return 0;
}