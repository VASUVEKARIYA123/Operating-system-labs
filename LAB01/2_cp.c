#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// 2). Implementation of cp command with following features
//      a. Destination file already existing b. Destination file does not exist.

int main(int argc,char* argv[]){
    if(argc == 2){
        printf("you need to pass destination file name also...\n");
    }
	if(argc < 2 ){
        printf("you need to pass a two arguments...\n");
        return 1;
    }

	// printf("argc : %d\n",argc);

    // for(int i = 0 ; i <argc ; i++){
    //     printf("file %d : %s\n",i,argv[i]);
    // }

    char buf[1000];

    //open first file in read mode
    int fd;
	fd = open(argv[1],O_RDONLY|O_CREAT);
	// printf("file 1 READ : %d\n",fd);

    //open second file in write mode 
    int fd2 ;
    fd2 = open(argv[2],O_WRONLY|O_CREAT,0777);
	// printf("file 2 WRITE : %d\n",fd2);

    //read from first file
    int readByte = read(fd,buf,sizeof(buf));
    
    //write in second file
    int writeByte = write(fd2,buf,readByte );

	
    // printf("byte read : %d\n",readByte);
    // printf("byte write : %d\n",writeByte);

    //close both file
	int close1 = close(fd);
    int close2 = close(fd2);

return 0;
}
