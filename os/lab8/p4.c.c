#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>

int shared;
sem_t sem1,sem2;
int value1, value2;

void* func1()
{
	sem_wait(&sem1);
	sem_getvalue(&sem1, &value1);
	printf("In function 1 with value of sem1: %d \n", value1);
	sem_wait(&sem2);
}

void* func2()
{
	sem_wait(&sem2);
	sem_getvalue(&sem2, &value2);
	printf("In function 1 with value of sem2: %d \n", value2);
	sem_wait(&sem1);
}

void main()
{
	pthread_t tid1,tid2;
	sem_init(&sem1,0,1);
	sem_init(&sem2,0,1);
	pthread_create(&tid1,NULL,func1,NULL);
	pthread_create(&tid2,NULL,func2,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
}