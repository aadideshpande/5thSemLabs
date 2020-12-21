#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

sem_t wrt;
sem_t mutex;
int count = 1;
int readcount = 0;

void *writer()
{   
    sem_wait(&wrt);
    count = count+1;
    printf("Writer: modified count to %d\n",count);
    sem_post(&wrt);

}
void *reader()
{   
    sem_wait(&mutex);
    readcount++;
    if(readcount == 1) {
        sem_wait(&wrt);
    }
    sem_post(&mutex);
    printf("Reader: read count as %d\n",count);
    printf("No of readers %d\n",readcount);

    sem_wait(&mutex);
    readcount--;
    if(readcount == 0) {
        sem_post(&wrt);
    }
    sem_post(&mutex);
}

int main()
{   

    pthread_t tid1,tid2;
    sem_init(&mutex,0,1);
    sem_init(&wrt,0,1);

    for(int i = 0; i < 10; i++) {
        pthread_create(&tid1, NULL, reader, NULL);
        pthread_create(&tid2, NULL, writer, NULL);
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
    
}