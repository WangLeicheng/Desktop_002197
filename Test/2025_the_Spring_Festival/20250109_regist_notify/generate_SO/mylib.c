#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#include <string.h>

typedef struct {
	char* name;
	int name_length;
	int age;
} people_t;

typedef enum {
	FRESHMAN = 1,
	SOPHOMORE,
	JUNIOR,
	SENIOR,
} E_GRADE;

typedef struct {
	people_t* person;
	E_GRADE grade;
} student_t;


typedef void (*MYLIB_NOTIFIER)(void* pUserData);

// A structure to represent the task with a timeout
typedef struct {
    MYLIB_NOTIFIER notify;
    int timeout;  // Timeout in seconds
} task_info_t;

// Simulate a long-running task (e.g., performing a complex calculation)
void *long_running_task(void *arg)
{
    task_info_t *task_info = (task_info_t *)arg;

    // Simulate work (e.g., sleep for 3 seconds)
    printf("Task started... waiting for 3 seconds...\n");
    sleep(3);

    // Call the callback function to notify the caller that the task is complete
    student_t *p_student = (student_t *)malloc(sizeof(student_t));
    p_student->person = (people_t *)malloc(sizeof(people_t));
    p_student->person->name = strdup("wlc");
    p_student->person->name_length = strlen(p_student->person->name);
    p_student->person->age = 28;
    p_student->grade = FRESHMAN;

    if (task_info->notify) {
        task_info->notify((void*)p_student);  // Example result (42)
    }

    free(p_student->person->name);
    free(p_student->person);
    free(p_student);

    free(task_info);  // Free the task info after the task is done
    return NULL;
}

// Function to start the task and allow a callback with timeout handling
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

    // Create a thread to perform the task asynchronously
    int ret = pthread_create(&thread, NULL, long_running_task, (void *)task_info);
    if (ret != 0) {
        perror("Failed to create task thread");
        free(task_info);
        return -1;
    }

    // Wait for the task to finish with a timeout (using select for simplicity)
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += timeout;  // Set timeout duration

    // Wait for the thread to finish or timeout
    ret = pthread_timedjoin_np(thread, NULL, &ts);
    if (ret == 0) {
        printf("Task completed within timeout.\n");
        return 0;
    } else {
        printf("Task timed out after %d seconds.\n", timeout);
        pthread_cancel(thread);  // Cancel the task if it times out
        return -1;
    }
}
