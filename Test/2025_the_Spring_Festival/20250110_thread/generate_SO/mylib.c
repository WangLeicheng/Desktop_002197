#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#include <string.h>



typedef struct {
    char *name;
    int age;
} student_t;

typedef void (*MYLIB_NOTIFIER)(void* taskResult);

typedef struct {
    MYLIB_NOTIFIER notify;
    int timeout;
} task_info_t;


void *doing_task(void *arg)
{
    task_info_t *task_info = (task_info_t *)arg;
    printf("Task stated.. waiting for 3 seconds...\n");
    sleep(3);
    

    student_t *p_student = (student_t *)malloc(sizeof(student_t));
    p_student->name = strdup("wlc");
    p_student->age = 28;

    if (task_info->notify) {
        task_info->notify((void *)p_student);
    }

    free(p_student->name);
    free(p_student);
    
    free(task_info);
    return NULL;
}

int perform_task(MYLIB_NOTIFIER notify, int timeout)
{
    pthread_t thread;
    task_info_t *task_info = (task_info_t *)malloc(sizeof(task_info_t));

    if (task_info == NULL) {
        perror("Failed to allocate memory for task_info");
        return -1;
    }

    task_info->notify = notify;
    task_info->timeout = timeout;

    int ret = pthread_create(&thread, NULL, doing_task, (void *)task_info);
    if (ret != 0) {
        perror("Failed to create task thread");
        free(task_info);
        return -1;
    }

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += timeout;
    
    ret = pthread_timedjoin_np(thread, NULL, &ts);
    if (ret == 0) {
        printf("\033[32mTask completed within timeout.\033[0m\n");
        return 0;
    } else {
        printf("\033[31mTask timed out after %d seconds.\033[0m\n", timeout);
        pthread_cancel(thread);
        return -1;
    }
}
