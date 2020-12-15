#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>

void main()
{
	char fname[100];
    char new_path[100]="newfile.txt";
    struct stat start;

    printf("enter the file name \n");
    scanf("%s", fname);

    printf("before the linking: \n");
    system("ls -il *.txt");
    int ret = symlink(fname, new_path);

    ret = unlink(fname);
    printf("afterlinking: \n");
    system("ls -il *.txt");    

}