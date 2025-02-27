#include <stdio.h>
#include <stdlib.h>
#include "list_t.h"
#include "list.h"

typedef struct ST_STUDENT {
    int age;
    list_t list;  // This links the student to the doubly linked list
} ST_STUDENT;

static LIST_HEAD(my_student_1); // Initialize the head of the list
static LIST_HEAD(my_student_2); // Initialize the head of the list

int main()
{
    // Dynamically create 5 student elements and add them to the list
    for (int i = 0; i < 5; ++i) {
        struct ST_STUDENT *elem = malloc(sizeof(*elem));  // Allocate memory for the student
        if (!elem) {
            perror("malloc failed");
            return 1;
        }
        elem->age = i; // Assign a sample age for the student (for example, 20, 21, ..., 24)
        INIT_LIST_HEAD(&elem->list); // Initialize the list element

        list_add_tail(&elem->list, &my_student_1); // Add the student to the list
    }

    // Iterate over the list and print the ages of the students
    list_t *pos;
    list_for_each(pos, &my_student_1) {
        // Cast pos from list_t* to ST_STUDENT* and print the student's age
        // Use list_entry to get the containing ST_STUDENT structure
        struct ST_STUDENT *student = list_entry(pos, struct ST_STUDENT, list);
        printf("%d-->", student->age); // Print each student's age
    }
    printf("\n");

    for (int i = 5; i < 10; ++i) {
        struct ST_STUDENT *elem = malloc(sizeof(*elem));  // Allocate memory for the student
        if (!elem) {
            perror("malloc failed");
            return 1;
        }
        elem->age = i; // Assign a sample age for the student (for example, 20, 21, ..., 24)
        INIT_LIST_HEAD(&elem->list); // Initialize the list element

        list_add_tail_2(&elem->list, &my_student_2); // Add the student to the list
    }

    // Iterate over the list and print the ages of the students
    list_for_each(pos, &my_student_2) {
        // Cast pos from list_t* to ST_STUDENT* and print the student's age
        // Use list_entry to get the containing ST_STUDENT structure
        struct ST_STUDENT *student = list_entry(pos, struct ST_STUDENT, list);
        printf("%d-->", student->age); // Print each student's age
    }
    printf("\n");

    list_splice_2(&my_student_1, &my_student_2);
    list_for_each(pos, &my_student_2) {
        // Cast pos from list_t* to ST_STUDENT* and print the student's age
        // Use list_entry to get the containing ST_STUDENT structure
        struct ST_STUDENT *student = list_entry(pos, struct ST_STUDENT, list);
        printf("%d-->", student->age); // Print each student's age
    }
    printf("\n");

    return 0;
}

