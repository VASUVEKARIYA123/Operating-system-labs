#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>



int main(){
	
	
    char buf[1000];

    //open first file in read mode
    int fd;
	fd = open("1.txt",O_RDONLY|O_CREAT);
	printf("file 1 READ : %d\n",fd);

    //open second file in write mode 
    int fd2 ;
    fd2 = open("2.txt",O_WRONLY|O_CREAT,0777);
	printf("file 2 WRITE : %d\n",fd2);

    //read from first file
    int readByte = read(fd,buf,sizeof(buf));
    
    //write in second file
    int writeByte = write(fd2,buf,readByte );

	
    printf("byte read : %d\n",readByte);
    printf("byte write : %d\n",writeByte);

    //close both file
	int close1 = close(fd);
    int close2 = close(fd2);

return 0;
}
