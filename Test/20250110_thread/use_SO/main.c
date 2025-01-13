#include "mylib.h"

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <time.h>

sem_t sem;
student_t* gp_student = NULL;


// print the information of the student
void print_student(const student_t *student)
{
    if (student == NULL) {
        printf("The pointer to student is NULL\n");
        return;
    }
    
    printf("\033[31mThe student's name is : %s\033[0m\n", student->name);
    printf("\033[31mThe student's age is : %d\033[0m\n", student->age);
}



// Define the callback function
void task_callback(void* result) 
{
    student_t* p_student = (student_t *)result;

    // Allocate memory for the global student and perform a deep copy
    gp_student = malloc(sizeof(student_t));  // Allocate memory for student
    if (!gp_student) {
        perror("Failed to allocate memory for global student");
        return;
    }

    gp_student->name = strdup(p_student->name);  // Deep copy of the name string
    gp_student->age = p_student->age;

    sem_post(&sem);
}

void* print_every_second_thread(void *arg)
{
    while(1) {

        struct timeval tv;
        struct tm *tm_info;

        // Get current time in seconds and microseconds
        gettimeofday(&tv, NULL);

        // Convert time to tm struct
        tm_info = localtime(&tv.tv_sec);

        // Print formatted time including milliseconds
        printf("\033[34mThis will appear every seconds. Current Time: %02d:%02d:%02d.%03ld\033[0m\n",            
               tm_info->tm_hour,
               tm_info->tm_min,
               tm_info->tm_sec,
               tv.tv_usec / 1000);  // Milliseconds
        sleep(1);
    }
}

// Supervisor thread function to monitor the callback completion
void* supervisor_thread(void* arg) 
{
    printf("Supervisor thread waiting for callback...\n");

    // Wait for the semaphore to be posted by the callback
    sem_wait(&sem);
    // Print the global student details
    printf("Supervisor thread: Callback completed!\n");
    printf("Global Student Information:\n");
    print_student(gp_student);

    printf("Supervisor thread: Callback completed!\n");
    return NULL;
}
    

int main() 
{
    // Initialize the semaphore with value 0 (will wait until signaled)
    sem_init(&sem, 0, 0);

    // Create another thread to every seconds printf
    pthread_t print_time;
    if (pthread_create(&print_time, NULL, print_every_second_thread, NULL) != 0) {
        perror("Failed to create print every second thread");
        return -1;
    }   

    // Create the supervisor thread

    pthread_t supervisor;
    if (pthread_create(&supervisor, NULL, supervisor_thread, NULL) != 0) {
        perror("Failed to create supervisor thread");
        return -1;
    }

   
    int timeout = 5;  // Set a timeout of 5 seconds
    int ret = perform_task(task_callback, timeout);
    if (ret == 0) {
        printf("Task completed successfully.\n");
    } else {
        printf("Task failed or timed out.\n");
    }

    // Wait for the supervisor thread to finish
    // pthread_join(print_time, NULL);
    pthread_join(supervisor, NULL);

    // Clean up the semaphore
    sem_destroy(&sem);

    return 0;
}
