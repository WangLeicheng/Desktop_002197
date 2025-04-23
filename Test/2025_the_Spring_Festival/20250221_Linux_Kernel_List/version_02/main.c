#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define MAX_NAME 100

// Define the type identifiers for each structure
#define MY_DATA_TYPE 1
#define MY_OTHER_DATA_TYPE 2

// Define the first structure (my_data)
struct my_data {
    int type;  // Field to distinguish structure type
    char name[MAX_NAME];
    int age;
    struct list_head list;
};

// Define the second structure (my_other_data)
struct my_other_data {
    int type;  // Field to distinguish structure type
    char description[MAX_NAME];
    float value;
    struct list_head list;
};

char *names[5] = {"wlc", "hhr", "zxm", "aqbj", "sby"};
int ages[5] = {28, 26, 28, 27, 26};

char *descriptions[3] = {"Desc 1", "Desc 2", "Desc 3"};
float values[3] = {10.5, 20.5, 30.5};

int main() {
    // Initialize a single list head to hold both structures
    LIST_HEAD(my_list);

    // Add elements of my_data to the list
    for (int i = 0; i < 5; ++i) {
        struct my_data *elem = malloc(sizeof(*elem));
        if (!elem) {
            perror("malloc failed");
            return -1;
        }

        elem->type = MY_DATA_TYPE;  // Mark the type of structure
        strncpy(elem->name, names[i], MAX_NAME - 1);
        elem->name[MAX_NAME - 1] = '\0';  // Ensure null-termination
        elem->age = ages[i];

        INIT_LIST_HEAD(&elem->list);
        list_add_tail(&elem->list, &my_list);
    }

    // Add elements of my_other_data to the list
    for (int i = 0; i < 3; ++i) {
        struct my_other_data *elem = malloc(sizeof(*elem));
        if (!elem) {
            perror("malloc failed");
            return -1;
        }

        elem->type = MY_OTHER_DATA_TYPE;  // Mark the type of structure
        strncpy(elem->description, descriptions[i], MAX_NAME - 1);
        elem->description[MAX_NAME - 1] = '\0';  // Ensure null-termination
        elem->value = values[i];

        INIT_LIST_HEAD(&elem->list);
        list_add_tail(&elem->list, &my_list);
    }

    // Print all elements in the list (regardless of type)
    printf("List contents:\n");

    struct list_head *pos;
    list_for_each(pos, &my_list) {
        // Check the type of the element using the `type` field
        if (list_entry(pos, struct my_data, list)->type == MY_DATA_TYPE) {
            struct my_data *data_elem = list_entry(pos, struct my_data, list);
            printf("[my_data: %s, %d] -> ", data_elem->name, data_elem->age);
        } else if (list_entry(pos, struct my_other_data, list)->type == MY_OTHER_DATA_TYPE) {
            struct my_other_data *other_elem = list_entry(pos, struct my_other_data, list);
            printf("[my_other_data: %s, %.2f] -> ", other_elem->description, other_elem->value);
        }
    }
    printf("\n");

    // Cleanup: free the list elements
    struct list_head *n;
    list_for_each_safe(pos, n, &my_list) {
        if (list_entry(pos, struct my_data, list)->type == MY_DATA_TYPE) {
            struct my_data *data_elem = list_entry(pos, struct my_data, list);
            free(data_elem);  // Free my_data element
        } else if (list_entry(pos, struct my_other_data, list)->type == MY_OTHER_DATA_TYPE) {
            struct my_other_data *other_elem = list_entry(pos, struct my_other_data, list);
            free(other_elem);  // Free my_other_data element
        }
    }

    return 0;
}
