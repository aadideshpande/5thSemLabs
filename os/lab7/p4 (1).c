#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

void* oddSum(void* i)
{
	int val = (int)i;
	int sum=0;
	for(int j=1;j<=val;j++)
	{
		if(j%2 == 1)
			sum+=j;
	}
	return (void*)sum;
}

void* evenSum(void* i)
{
	int val = (int)i;
	int sum=0;
	for(int j=1;j<=val;j++)
	{
		if(j%2 == 0)
			sum+=j;
	}
	return (void*)sum;
}

void main()
{
	pthread_t thread[2];
	int even,odd,n;
	printf("Enter the upper limit for even and odd sum calculation: \n");
	scanf("%d",&n);
	pthread_create(&thread[0],0,&evenSum,(void*)n);
	pthread_create(&thread[1],0,&oddSum,(void*)n);
	pthread_join(thread[0],(void**)&even);
	pthread_join(thread[1],(void**)&odd);
	printf("The even sum is: %d\n",even);
	printf("The odd sum is: %d\n",odd);
	exit(0);
}