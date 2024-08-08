#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>

// 3. WAP to create simple calculator using threads.

struct node{
    int a;
    int b;
};
void* add(void* x){
    // function for thread 1
    struct node* s = (struct node*)x;
    int num1 = s->a;
    int num2 = s->b;
    
    printf("inside sum\n");
    printf("sum: %d+%d=%d\n\n",num1,num2,num1+num2);
}
void* sub(void* x){
    // function for thread 1
    struct node* s = (struct node*)x;
    int num1 = s->a;
    int num2 = s->b;

    printf("inside sub\n");
    printf("sub: %d-%d=%d\n\n",num1,num2,num1-num2);
}
void* mul(void* x){
    // function for thread 1
    struct node* s = (struct node*)x;
    int num1 = s->a;
    int num2 = s->b;

    printf("inside mul\n");
    printf("mul: %d*%d=%d\n\n",num1,num2,num1*num2);
}
void* div(void* x){
    // function for thread 1
    struct node* s = (struct node*)x;
    int num1 = s->a;
    int num2 = s->b;

    printf("inside div\n");
    printf("div: %d/%d=%d\n\n",num1,num2,num1/num2);
}

int main(){

    
    int num = 10;
    struct node n1;
    n1.a = 100;
    n1.b = 50;
    
    printf("inside main  \n");
    pthread_t sumt;
    pthread_create(&sumt,NULL,add,&n1); 
    pthread_join(sumt,NULL);

    pthread_t subt;
    pthread_create(&subt,NULL,sub,&n1); 
    pthread_join(subt,NULL);

    pthread_t mult;
    pthread_create(&mult,NULL,mul,&n1); 
    pthread_join(mult,NULL);

    pthread_t divt;
    pthread_create(&divt,NULL,div,&n1); 
    pthread_join(divt,NULL);
    
    
    
   
    
    return 0;
}