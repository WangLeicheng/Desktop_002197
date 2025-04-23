#include <stdio.h>
#include <pthread.h>

void *thread_fun_01(void *arg)
{
	while (1) {
		printf("This is the thread 01 call\n");
	}
}

void *thread_fun_02(void *arg)
{
	while (1) {
		printf("This is the thread 02 call\n");
	}
}

int main()
{
	pthread_t t_1;
	pthread_t t_2;
	pthread_create(&t_1, NULL, thread_fun_01, NULL);
	pthread_create(&t_2, NULL, thread_fun_02, NULL);

	pthread_join(t_1, NULL);
	pthread_join(t_2, NULL);

	return 0;
}
