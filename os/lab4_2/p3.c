#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>

void main()
{
	char fname[100];
    char new_path[100]="newfile.txt";
    struct stat start;

    printf("enter the file name \n");
    scanf("%s", fname);
    int ret1 = stat(fname,&start);

    printf("Number of hard links:%ld\n", start.st_nlink);
    system("ls -il *.txt");
    printf("linking begins\n");

    int ret2 = link(fname,new_path);
    struct stat temp;
    int ret3 = stat(fname,&temp);
    printf("Number of hard links:%ld\n", temp.st_nlink);
    printf("New path:%s\n",new_path);
    system("ls -il *.txt");
    int ret4 = unlink(fname);
    struct stat end;
    int ret5 = stat(new_path,&end);
    printf("unlinking now\n");
    printf("Number of hard links after unlinking:%ld\n", end.st_nlink);
}