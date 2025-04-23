#include <stdio.h>
#include <string.h>

int main()
{
    char str[] = "Hello, World!";

    char dest[20];

    int n = sizeof(str) / sizeof(str[0]);

    printf("size of str is %d\n", n);

    memcpy(dest, str, sizeof(str) / sizeof(str[0]));

    printf("%s\n", dest);

    return 0;
}

