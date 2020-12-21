#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>
#include<sys/wait.h>

void* getFibo(int arr[])
{
	arr[1]=0;
	arr[2]=1;
	for(int i=3;i<=arr[0];i++)
	{
		arr[i]=arr[i-1]+arr[i-2];
	}
}

int main(int argc,char** argv)
{
	if(argc != 2)
	{
		printf("You have to enter the number of Fibonacci no.s to generate via cmd line.\n");
		exit(1);
	}
	int arr[100];
	arr[0]=atoi(argv[1]);
	pthread_t t1;
	pthread_create(&t1,0,&getFibo,(void*)arr);
	pthread_join(t1,0);
	printf("The first %d fibonacci numbers are:",arr[0]);
	for(int i=1;i<=arr[0];i++)
	{
		printf("%d, ",arr[i]);
	}
	printf("\n");
	return 0;
}