#include <stdio.h>
#include <stdlib.h>

void test()
{
    int *a = (int *)malloc(sizeof(int));
    *a = 10;
    int *b = a;
    int *c = (int *)malloc(sizeof(int));
    *c = *a;
    printf("the a is %d, the b is %d, the c is %d\n", *a, *b, *c);

    *a = 20;
    printf("the a is %d, the b is %d, the c is %d\n", *a, *b, *c);
}

int main()
{
    test();
    return 0;
}
