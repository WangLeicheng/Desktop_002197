#include <stdio.h>
#include <pthread.h>


int g_number;

void *foo_01(void *arg)
{
    while(1) {
        g_number = 1;
        sleep(1);
        printf("\033[34mThe number is %d\033[0m\n", g_number);
    }
}

void *foo_02(void *arg)
{
    while(1) {
        g_number = 2;
        sleep(1);
        printf("\033[32mThe number is %d\033[0m\n", g_number);
   }
}

int main()
{
    pthread_t thread_01;
    pthread_t thread_02;

    pthread_create(&thread_01, NULL, foo_01, NULL);
    pthread_create(&thread_02, NULL, foo_02, NULL);

    pthread_join(thread_01, NULL);
    pthread_join(thread_02, NULL);
    return 0;
}


