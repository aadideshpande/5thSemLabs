#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

void* threadFunc(void* i)
{
	int val = (int)i;
	int sum = (val*(val+1))/2;
	return (void*)sum;
}

void main()
{
	pthread_t thread;
	int n,res;
	printf("Enter upper limit for sum calculation: \n");
	scanf("%d",&n);
	pthread_create(&thread,0,&threadFunc,(void*)n);
	pthread_join(thread,(void**)&res);
	printf("The sum is: %d\n",res);
	exit(0);
}