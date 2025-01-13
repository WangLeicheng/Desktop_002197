#ifndef MYLIB_H
#define MYLIB_H

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

// Define the callback function type
typedef void (*MYLIB_NOTIFIER)(void* result);

// Function to perform the task with a callback and timeout
int perform_task(MYLIB_NOTIFIER p_notify, int timeout);

#endif // MYLIB_H

