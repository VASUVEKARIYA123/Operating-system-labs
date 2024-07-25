#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

//1). Implementation of cat command with echo and file concatenation functionalities.

int main(int argc,char* argv[]){
    char buf[1000];

    // printf("argc : %d",argc);

    // for(int i = 0 ; i < argc ; i++)
    // {
    //     printf("argument %d : %s\n",i+1,argv[i]);
    // }

    if(argc == 1){
        int readByte;
        do{
            readByte = read(0,buf,sizeof(buf));
            write(1,buf,readByte);
        }while(readByte > 0);

    }
    else if(argc > 1){
        for(int i = 1 ; i < argc ; i++){
            int fd;
            fd = open(argv[i],O_RDONLY);
            if(fd == -1 ) continue;
            int readByte = read(fd,buf,sizeof(buf));
            write(1,buf,readByte);
            int close1 = close(fd);
        }

    }


    return 0;
}
