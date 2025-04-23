#include <stdio.h>
#include <semaphore.h>

#pragma pack(push, 8)

typedef struct {
	sem_t task_sem;
	int a;
} task_t;

int main()
{
	task_t task_01;
	printf("%ld\n", sizeof(task_01));


	return 0;
}
	
