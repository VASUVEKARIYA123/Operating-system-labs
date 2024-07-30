#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
// fork
int main(){
    printf("Before fork\n");
    int i =1;
    

    // When you do fork() , a whole process will be created including variables. So i in the parent is not i of the child. They have same virtual address but not same physical address. The modification is completely independent.
    if(fork()==0){
        i = i +1;
        printf("After fork %d %i\n",i,&i);

    }
    else{
        i = i +2;
        printf("After fork %d %i\n",i,&i);
    }
    return 0;
}