// caller.c
#include <stdio.h>

extern const char* get_hello();

int main() {
    const char* msg = get_hello();
    printf("Received from server: %s\n", msg);
    return 0;
}

