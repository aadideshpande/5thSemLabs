#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{

	//create a pipe
	int fd;
	char * my_fifo = "/tmp/my_fifo";
	mkfifo(my_fifo, 0777);
	
	//arrays to store the message
	char arr1[80], arr2[80];
	
	while (1)
	{
		//write a message to the pipe
		fd = open(my_fifo, O_WRONLY);
		printf("Enter The message\n");
		scanf("%s", arr2);
		write(fd, arr2, strlen(arr2)+1);
		close(fd);

		//read a message from the pipe
		fd = open(my_fifo, O_RDONLY);
		read(fd, arr1, sizeof(arr1));
		printf("FIFO 2: %s\n", arr1);
		close(fd);
	}
	return 0;
}