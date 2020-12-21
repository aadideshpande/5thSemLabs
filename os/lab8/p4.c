#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>

int shared;
sem_t b, c;
sem_t seat;
int seats = 5;

void* barber()
{
	while(1)
	{
		printf("idle barber \n");
		sem_wait(&c);
		sem_wait(&seat);
		printf("barber is now working \n");
		seats++;
		sem_post(&seat);
		sem_post(&c);
	}
}

void* customer()
{
	while(1)
	{
		if(seats > 0)
		{
			seats--;
			sem_post(&c);

			sem_wait(&b);
			sem_wait(&seat);
			printf("customer's chance for a haircut has finally come\n");
			sleep(2);
			seats++;
			sem_post(&seat);
			sem_post(&b);
			printf("Customer has finished his haircut\n");
		}
		else
		{
			printf("shop full\n");
			sleep(2);
		}
	}
}

void main()
{

	pthread_t tid1,tid2;
	sem_init(&b,0,1);
	sem_init(&c,0,1);
	sem_init(&seat,0,1);
	pthread_create(&tid1,NULL,barber,NULL);
	pthread_create(&tid2,NULL,customer,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
}