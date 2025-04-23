#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10

// Structure to hold shared resources
typedef struct {
    int buffer[BUFFER_SIZE];
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t cond_empty;
    pthread_cond_t cond_full;
} SharedData;

// Producer function
void* producer(void* arg) {
    SharedData* data = (SharedData*)arg;

    for (int i = 0; i < 20; i++) {
        pthread_mutex_lock(&data->mutex);

        // Wait until there's space in the buffer
        while (data->count == BUFFER_SIZE) {
            pthread_cond_wait(&data->cond_empty, &data->mutex);
        }

        // Produce an item
        data->buffer[data->count] = i;
        data->count++;
        printf("Produced: %d, Buffer count: %d\n", i, data->count);

        // Signal consumer that buffer is not empty
        pthread_cond_signal(&data->cond_full);

        pthread_mutex_unlock(&data->mutex);

        // Simulate some work (sleep)
        sleep(1);
    }

    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    SharedData* data = (SharedData*)arg;

    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&data->mutex);

        // Wait until there's something to consume
        while (data->count == 0) {
            pthread_cond_wait(&data->cond_full, &data->mutex);
        }

        // Consume an item
        int item = data->buffer[data->count - 1];
        data->count--;
        printf("Consumed: %d, Buffer count: %d\n", item, data->count);

        // Signal producer that buffer is not full
        pthread_cond_signal(&data->cond_empty);

        pthread_mutex_unlock(&data->mutex);

        // Simulate some work (sleep)
        sleep(1);
    }

    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize shared data
    SharedData data = {
        .count = 0,
        .mutex = PTHREAD_MUTEX_INITIALIZER,
        .cond_empty = PTHREAD_COND_INITIALIZER,
        .cond_full = PTHREAD_COND_INITIALIZER
    };

    // Create the producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, &data);
    pthread_create(&consumer_thread, NULL, consumer, &data);

    // Wait for both threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Cleanup (destroy mutex and condition variables)
    pthread_mutex_destroy(&data.mutex);
    pthread_cond_destroy(&data.cond_empty);
    pthread_cond_destroy(&data.cond_full);

    return 0;
}

