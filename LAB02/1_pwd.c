#include<stdio.h>
#include<unistd.h>

// 1). Implementation of pwd command.

int main(int argc,char* argv[]){

    char buf[1000];
    char* ans;

    //get currunt working directory
    ans = getcwd(buf,sizeof(buf));

    // printf("ans : %s\n",ans);

    printf("buf ; %s\n",buf);
    // write(1,buf,sizeof(buf));

    return 0;
}