#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
int main()
{
	pid_t pid;
	pid = fork();
	if(pid < 0)
	{
		printf("error in creating child process \n");
	}
	else if(pid == 0)
	{
		printf("now in child process pid = %d \n", pid);
		exit(-1);
	}
	else
	{
		sleep(10);
	}
}
