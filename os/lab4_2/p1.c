#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
int main()
{
	struct stat sb;
	int ret;
	char fname[100];
	printf("enter the file name: \n");	
	scanf("%s", fname);

	ret = stat(fname, &sb);
	if(ret)
	{
		perror("stat");
	}
	else
	{
		printf("the inod number of file is: %ld \n",sb.st_ino);
	}
}

