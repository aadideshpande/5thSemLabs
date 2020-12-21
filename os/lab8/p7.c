#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

void* threadFunc(int args[])
{
	int begin = (int)args[0];
	int end = (int)args[1];
	int num = 0;

	for(int i=begin ;i <= end; i++)
	{
		int factors = 0;
		for(int j = 2; j < i; j++)
		{
			if(i % j == 0)
			{
				factors++;
				break;
			}
		}
		if(factors == 0)
		{
			num++;
			printf("%d, ",i);
		}
	}
	printf("\n");
	return (void*)num;
}

void main()
{
	pthread_t thread;
	int res, bound[2];
	printf("Enter the lower & upper limit for prime number calculation: \n");
	scanf("%d %d",&bound[0],&bound[1]);
	pthread_create(&thread,0,&threadFunc,(void*)bound);
	pthread_join(thread,(void**)&res);
	printf("Total prime numbers is: %d\n",res);
	exit(0);
}