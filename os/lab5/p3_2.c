#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
	//create a pipe
	int fd1;
	char * my_fifo = "/tmp/my_fifo";
	mkfifo(my_fifo, 0777);
	
	//array to store the messages
	char arr1[80], arr2[80];
	while (1)
	{
		// first we read from the pipe
		fd1 = open(my_fifo,O_RDONLY);
		read(fd1, arr1, 80);
		printf("FIFO 1: %s\n", arr1);
		close(fd1);

		// then we write to the pipe
		fd1 = open(my_fifo,O_WRONLY);
		printf("Enter The message\n");
		scanf("%s", arr2);
		write(fd1, arr2, strlen(arr2)+1);
		close(fd1);
	}
	return 0;
}