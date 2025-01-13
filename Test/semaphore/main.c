#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


sem_t sem;

void* thread_func(void* arg)
{
	sem_wait(&sem);

	printf("Thread's id is %ld \n", (long)(arg));

	sleep(1);

	sem_post(&sem);

	return NULL;
}


int main()
{
	pthread_t threads[5];

	long i;

	sem_init(&sem, 0, 2);

	for (i = 0; i < 5; ++i) {
		pthread_create(&threads[i], NULL, thread_func, (void*)i);
	}

	for (i = 0; i < 5; ++i) {
		pthread_join(threads[i], NULL);
	}

	sem_destroy(&sem);
	return 0;
}
