#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define BUFFER_SIZE 10
#define BUFFER_ITEMS 10

typedef struct
{
	int buffer[BUFFER_SIZE];
	sem_t empty,full,mutex;
}samaphore;

int in=0,out=0;
samaphore*ptr;

sem_t empty,full,mutex;

void *producer(void *arg) 
{
    int produced_items=BUFFER_ITEMS;

    while(produced_items>0)
    {
        int item=rand()%100;
        sem_wait(&ptr->empty);  
        sem_wait(&ptr->mutex);  
        ptr->buffer[in]=item;
        printf("Produced: %d\n",item);
        in=(in+1)%BUFFER_SIZE;
        sem_post(&ptr->mutex);  
        sem_post(&ptr->full);   
        produced_items--;
        sleep(rand()%5);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg) 
{
    int consumed_items= BUFFER_ITEMS;

    while(consumed_items>0) 
    {
        sem_wait(&ptr->full);  
        sem_wait(&ptr->mutex);  
        int item = ptr->buffer[out];
        printf("Consumed: %d\n", item);
        out=(out+1)%BUFFER_SIZE;
        sem_post(&ptr->mutex);  
        sem_post(&ptr->empty);  
        consumed_items--;
        sleep(rand()%5);
    }
    pthread_exit(NULL);
}

int main() 
{
    pthread_t producer_thread, consumer_thread;
    ptr=(samaphore*)malloc(sizeof(samaphore));
    sem_init(&ptr->empty,0,BUFFER_SIZE);
    sem_init(&ptr->full,0,0);
    sem_init(&ptr->mutex,0,1);
    pthread_create(&producer_thread,NULL,producer,NULL);
    pthread_create(&consumer_thread,NULL,consumer,NULL);
    pthread_join(producer_thread,NULL);
    pthread_join(consumer_thread,NULL);
    sem_destroy(&ptr->empty);
    sem_destroy(&ptr->full);
    sem_destroy(&ptr->mutex);
    free(ptr);
    return 0;
}
