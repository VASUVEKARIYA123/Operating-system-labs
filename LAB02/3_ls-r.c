#include<sys/types.h>
#include<dirent.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

// 3). Implementation of recursive ls version.

void ls(char* path){

    DIR* d = opendir(path);
    struct dirent* de;
    while(de = readdir(d)){
        if(de->d_name[0] == '.') continue;
        printf("%s\t",de->d_name);
    }
    printf("\n");
    DIR* aa = opendir(path);
    struct dirent* a;
    while(a = readdir(aa)){
        if(a->d_name[0] == '.') continue;
        if(a->d_type==DT_DIR){
            char temp[1000];
            strcpy(temp, path);
            strcat(temp,"/");
            strcat(temp,a->d_name);
            printf("\n");
            printf("%s:\n",temp);
            ls(temp);
            printf("\n");
        }
    }
}
int main(){
    char buf[100];
    char* ans;

    ans = getcwd(buf,sizeof(buf));
    printf(".:\n");
    ls(ans);
    return 0;
}