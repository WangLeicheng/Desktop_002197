#include <stdio.h>
#include <pthread.h>

void *thread_func(void *a)
{
    printf("thread is running the print result is %d\n", *(int *)a);
    return "Finished";
}

int main()
{
    pthread_t thread;
    int a = 10;
    void *retval;
    pthread_create(&thread, NULL, thread_func, &a);
    // pthread_join(thread, NULL);
    pthread_join(thread, &retval);
    printf("Thread join, return value: %s\n", (char *)retval);
    
    return 0;
}
    

