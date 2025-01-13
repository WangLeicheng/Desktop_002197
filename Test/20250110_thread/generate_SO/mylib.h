#ifndef MYLIB_H
#define MYLIB_H

typedef struct {
    char *name;
    int age;
} student_t;

typedef void (*MYLIB_NOTIFIER)(void* taskResult);

int perform_task(MYLIB_NOTIFIER p_notify, int timeout);

#endif      // MYLIB_H
