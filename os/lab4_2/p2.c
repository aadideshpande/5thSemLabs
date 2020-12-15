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
		printf("ID of device containing file: %ld \n", sb.st_dev);
		printf("the inod number of file is: %ld \n",sb.st_ino);
		printf("the permissions: %d \n", sb.st_mode);	
		printf("the number of hard links: %ld, \n", sb.st_nlink);	
		printf("user id of owner: %d \n", sb.st_uid);
		printf("groud id of owner: %d \n", sb.st_gid);
		printf("the total size in bytes: %ld \n", sb.st_size);
		printf("blocksize for file system %ld \n", sb.st_blksize);
		printf("number of blocks allocated: %ld \n", sb.st_blocks);
		printf("last access time: %ld \n", sb.st_atime);
		printf("last modification time %ld \n", sb.st_mtime);
		printf("last status change time %ld \n", sb.st_ctime);
	}
}

