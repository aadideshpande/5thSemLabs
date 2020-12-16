#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
  
int main()
{
	//creation of pipe
	char *my_fifo="/tmp/my_fifo";
	mkfifo(my_fifo,0777);

	//various declarations
	int i=0,fd;
	//char str[80];
	int num;

	while(i<4)
	{
		//we only read from the pipe
		fd=open(my_fifo,O_RDONLY);
		read(fd, &num, sizeof(num)); 
		close(fd);
		printf("The number entered: %d \n", num); 
		i++;
	}
}