#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>

// 2. WAP to create a thread which should pass a character string to threaded function.
struct node{
    int a;
    int b;
};
void* fun1(void* x){
    // function for thread 1
    struct node* s = (struct node*)x;
    printf("inside thread %d %d\n",s->a,s->b);
}

void* fun2(void* str){
    //function for thread 2
    printf("inside thread %s\n",(char*)str);
}

int main(){

    
    int num = 10;
    struct node n1;
    n1.a = 12;
    n1.b = 13;
    char s[] = "vasu"; 
    //it was like thread pointer
    pthread_t t1;
    // we use it to create a thread
    pthread_create(&t1,NULL,fun1,&n1); 

    pthread_t t2;
    pthread_create(&t2,NULL,fun2,&s);

    // // if we join t1 and t2 thread then main process is wait for thread 1 and 2 to terminate 
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    printf("inside main  \n");
    
    return 0;
}