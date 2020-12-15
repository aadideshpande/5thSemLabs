#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
	pid_t pid;
	
	pid = fork();
	if(pid < 0)
	{
		printf("error in creating a child process \n");
		exit(-1);
	}
	else if(pid == 0) // for child process
	{
		printf("inside the child process \n");
		printf("the child PID is: %d \n", getpid());
		printf("the parent PID is: %d \n", getppid());
	}
	else
	{
		printf("inside the parent process \n");
		printf("the child PID is: %d \n", getpid());
		printf("the parent PID is: %d \n", getppid());
	}
}
