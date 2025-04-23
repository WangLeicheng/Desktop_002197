#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10

// Shared buffer
int buffer[BUFFER_SIZE];
int count = 0; // Number of items in the buffer

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_empty = PTHREAD_COND_INITIALIZER;  // Condition for buffer being empty
pthread_cond_t cond_full = PTHREAD_COND_INITIALIZER;   // Condition for buffer being full

// Producer function
void* producer(void* arg) {
    for (int i = 0; i < 20; i++) {
        pthread_mutex_lock(&mutex);

        // Wait until there's space in the buffer
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&cond_empty, &mutex);
        }

        // Produce an item
        buffer[count] = i;
        count++;
        printf("Produced: %d, Buffer count: %d\n", i, count);

        // Signal consumer that buffer is not empty
        pthread_cond_signal(&cond_full);

        pthread_mutex_unlock(&mutex);

        // Simulate some work (sleep)
        sleep(1);
    }

    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    for (int i = 0; i < 20; i++) {
        pthread_mutex_lock(&mutex);

        // Wait until there's something to consume
        while (count == 0) {
            pthread_cond_wait(&cond_full, &mutex);
        }

        // Consume an item
        int item = buffer[count - 1];
        count--;
        printf("Consumed: %d, Buffer count: %d\n", item, count);

        // Signal producer that buffer is not full
        pthread_cond_signal(&cond_empty);

        pthread_mutex_unlock(&mutex);

        // Simulate some work (sleep)
        sleep(1);
    }

    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Create the producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for both threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Cleanup (destroy mutex and condition variables)
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_empty);
    pthread_cond_destroy(&cond_full);

    return 0;
}

