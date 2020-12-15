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
        printf("process pid before is: %d \n", getppid());
    	sleep(5);	     
		printf("process pid after is: %d \n", getppid());
		exit(-1);
     }
     else
     {
		printf("now inside parent process \n");
        // sleep(10);
     }
}

