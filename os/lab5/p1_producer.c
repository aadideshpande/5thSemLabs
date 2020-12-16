#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
  
int main()
{

	// creation of the pipe
    char *my_fifo="/tmp/my_fifo";
    mkfifo(my_fifo,0777);

    // declarations
    int i=0,fd;
    //char arr[80];
    int num;

    while(i<4)
    {   
        // we open the pipe and write to it
        fd=open(my_fifo,O_WRONLY);
        printf("Enter the integer:\n");
        //fgets(arr, 80, stdin); 
        scanf("%d", &num);
        write(fd,&num,sizeof(num));
        close(fd);
        i++;
    }
}