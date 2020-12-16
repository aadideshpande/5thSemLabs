#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	int n;
	int fd[2];
	char buff[1025];
	char* msg = "welcome to manipal";

	// rerturn 2 file descriptors
	// fd[0] open for reading
	// fd[1] open for writing	
	// creation of a pipe
	pipe(fd);

	//write the data to the pipe
	write(fd[1], msg, sizeof(msg));
	
	// read the data from the pipe	
	n = read(fd[0], buff, 1025);

	if(n >= 0)
	{
		buff[n] = 0;
		printf("the msg obtained is: %s \n", buff);
	}
	else
	{
		perror("reading error");
	}
}
