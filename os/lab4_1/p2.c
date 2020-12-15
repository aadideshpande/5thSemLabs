#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

int main()
{
	pid_t pid;
	int n, status;
	pid = fork();	

	if(pid == -1)
	{
		printf("error while creating child process \n");
		exit(-1);
	}
	else if(pid == 0) // for child process
	{
		printf("now, execlp will execute \n");
		execlp("./a.out","p1", NULL);
	}
	
	// only the parent process will execute the below line	
	printf("program done for PID = %d \n", pid);
}
