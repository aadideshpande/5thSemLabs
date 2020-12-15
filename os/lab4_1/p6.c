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
	 int status;
     if(pid < 0)
     {
         printf("error in creating child process \n");
     }
     else if(pid == 0)
	 {
        sleep(5);	     
		exit(-1);
     }
     else
     {
		printf("now inside parent process \n");
        wait(&status);
		printf("status code is %d \n", status);
     }
}

