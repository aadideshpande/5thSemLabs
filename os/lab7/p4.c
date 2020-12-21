#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

sem_t customer;
sem_t barber;
sem_t seat;
int freeSeats;

void* barberFunc()
{
	while(1)
	{
		printf("barber is sitting idle\n");
		//waiting for a customer
		sem_wait(&customer);
		//blocking the seat
		sem_wait(&seat);
		printf("barber is working\n");
		sleep(2);
		freeSeats++;
		sem_post(&seat);
		sem_post(&customer);
	}
}

void* customerFunc()
{
	while(1)
	{
		if(freeSeats > 0)
		{
			freeSeats--;
			sem_post(&customer);

			sem_wait(&barber);
			sem_wait(&seat);
			printf("Customer is going to the Seat for a haircut\n");
			sleep(2);
			freeSeats++;
			sem_post(&seat);
			sem_post(&barber);
			printf("Customer has finished his haircut\n");
		}
		else
		{
			printf("Salon is full at the moment\n");
			sleep(2);
		}
	}
}

void main()
{
	freeSeats = 5;
	pthread_t tid1,tid2;
	sem_init(&customer,0,0);
	sem_init(&barber,0,1);
	sem_init(&seat,0,1);
	pthread_create(&tid1,NULL,barberFunc,NULL);
	pthread_create(&tid2,NULL,customerFunc,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
}