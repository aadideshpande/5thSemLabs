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
	int status, n;
	
	printf("main program has begun \n");
	pid = fork();
	if(pid == -1)
	{
		printf("error in creating child process \n");
		exit(-1);
	}
	else if(pid == 0) // for child process
	{
		printf("child executing \n");
		n = 10;
	}
	else // for parent process
	{
		n = 20;
		wait(&status);
		printf("now parent will execute \n");
	}
	
	for(int i = n; i < n + 10; i++)
	{
		printf("%d ", i);
	}
	printf("\n");
}
