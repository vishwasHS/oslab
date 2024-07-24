#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define BUFFER_ITEMS 10

typedef struct {
    int buffer[BUFFER_SIZE];
    sem_t empty;
    sem_t full;
    sem_t mutex;
} samaphore;

int in = 0, out = 0;
samaphore *ptr;

void *producer(void *arg) {
    int produced_items = BUFFER_ITEMS;

    while (produced_items > 0) {
        int item = rand() % 100;
        sem_wait(&ptr->empty);  
        sem_wait(&ptr->mutex);  
        ptr->buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;
        sem_post(&ptr->mutex);  
        sem_post(&ptr->full);   
        produced_items--;
        sleep(rand() % 5);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int consumed_items = BUFFER_ITEMS;

    while (consumed_items > 0) {
        sem_wait(&ptr->full);  
        sem_wait(&ptr->mutex);  
        int item = ptr->buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        sem_post(&ptr->mutex);  
        sem_post(&ptr->empty);  
        consumed_items--;
        sleep(rand() % 5);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;
    
    // Allocate memory for the samaphore structure
    ptr = (samaphore*) malloc(sizeof(samaphore));
    if (ptr == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory.\n");
        return 1;
    }

    // Initialize semaphores in the samaphore structure
    if (sem_init(&ptr->empty, 0, BUFFER_SIZE) != 0) {
        fprintf(stderr, "Error: Failed to initialize empty semaphore.\n");
        return 1;
    }
    if (sem_init(&ptr->full, 0, 0) != 0) {
        fprintf(stderr, "Error: Failed to initialize full semaphore.\n");
        return 1;
    }
    if (sem_init(&ptr->mutex, 0, 1) != 0) {
        fprintf(stderr, "Error: Failed to initialize mutex semaphore.\n");
        return 1;
    }

    // Create producer and consumer threads
    if (pthread_create(&producer_thread, NULL, producer, NULL) != 0) {
        fprintf(stderr, "Error: Failed to create producer thread.\n");
        return 1;
    }
    if (pthread_create(&consumer_thread, NULL, consumer, NULL) != 0) {
        fprintf(stderr, "Error: Failed to create consumer thread.\n");
        return 1;
    }

    // Join threads
    if (pthread_join(producer_thread, NULL) != 0) {
        fprintf(stderr, "Error: Failed to join producer thread.\n");
        return 1;
    }
    if (pthread_join(consumer_thread, NULL) != 0) {
        fprintf(stderr, "Error: Failed to join consumer thread.\n");
        return 1;
    }

    // Destroy semaphores
    sem_destroy(&ptr->empty);
    sem_destroy(&ptr->full);
    sem_destroy(&ptr->mutex);

    // Free allocated memory
    free(ptr);

    return 0;
}
