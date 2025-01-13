#include <stdio.h>
#include <stdlib.h>

void add(void* a, void* b)
{
	int* p1 = (int*)a;
	int* p2 = (int*)b;
	printf("the sum is %d\n", *p1 + *p2);
}

int main()
{
	int a = 10;
	int b = 20;
	int* p1 = &a;
	int* p2 = &b;

	void (*pFun)(void* a, void* b) = add;
	pFun(p1, p2);

	return EXIT_SUCCESS;
}
