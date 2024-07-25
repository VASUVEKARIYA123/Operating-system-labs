#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>



int main(){
	
	int fd;
	fd = open("1.txt",O_RDONLY|O_CREAT);
	printf("file 1 READ : %d\n",fd);

	int fd2 = open("1.txt",O_WRONLY|O_CREAT,0777);
	printf("file 1 WRITE : %d\n",fd2);

	int close1 = close(fd);
	int close2 = close(fd2);


return 0;
}
