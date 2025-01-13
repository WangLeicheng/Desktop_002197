#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread_func(void* arg) {
    pthread_mutex_lock(&mutex);
    printf("Thread has locked the mutex.\n");
    // Critical section
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t thread;
    
    // Create a thread
    pthread_create(&thread, NULL, thread_func, NULL);
    
    // Main thread also locks the mutex
    pthread_mutex_lock(&mutex);
    printf("Main thread has locked the mutex.\n");
    
    // Unlock the mutex in the main thread
    pthread_mutex_unlock(&mutex);
    
    // Wait for the thread to finish
    pthread_join(thread, NULL);
    
    return 0;
}

