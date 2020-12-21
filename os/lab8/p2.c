#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdlib.h>

int readcount;
sem_t mutex, wrt;
// mutex is used to ensure mutual exclusion
// when readcount is updated

int count = 1;

void* reader(void* arg)
{
	
	sem_wait(&mutex);
	readcount++;
	if(readcount == 1)
	{
		sem_wait(&wrt);
	}
	sem_post(&mutex);


	printf("count is: %d and readcount is %d \n",count, readcount);

	sem_wait(&mutex);
	readcount--;
	if(readcount == 0)
	{
		sem_post(&wrt);
	}
	sem_post(&mutex);
}

void* writer(void* arg)
{

	sem_wait(&wrt);
	count++;
	printf("writer count is: %d \n", count);
	sem_post(&wrt);
}

int main()
{
	int readcount = 0;
	pthread_t tid1, tid2;
	sem_init(&mutex, 0, 1);
	sem_init(&wrt, 0, 1);	

	for(int i = 0; i < 15; i++)\
	{
		pthread_create(&tid1, NULL, reader, NULL);
		pthread_create(&tid2, NULL, writer, NULL);
		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);
	}

	sem_destroy(&mutex);
	sem_destroy(&wrt);

}
	
		
