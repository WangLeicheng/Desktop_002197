#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

#define MAX_NAME 100

struct my_data {
    char name[MAX_NAME];
    int age;
    struct list_head list;
};

char *name[5]= {"wlc", "hhr", "zxm", "aqbj", "sby"};
int age[5] = {28, 26, 28, 27, 26};


static LIST_HEAD(my_list);

int main()
{

    for (int i = 0; i < 5; ++i) {
        struct my_data *elem = malloc(sizeof(*elem));
        strncpy(elem->name, name[i], MAX_NAME -1);
        elem->name[MAX_NAME - 1] = '\0';
        elem->age = age[i];
        INIT_LIST_HEAD(&elem->list);
        list_add_tail(&elem->list, &my_list);
    }

    struct my_data *pos;
    list_for_each_entry(pos, &my_list, list) {
        printf("[%s, %d]->", pos->name, pos->age);
    }
    printf("\n");

    // Normal order
    struct list_head *temp;
    list_for_each(temp, &my_list) {
        struct my_data *entry = list_entry(temp, struct my_data, list);
        printf("[%s, %d]->", entry->name, entry->age);
    }
    printf("\n");

    // Reverse order
    struct list_head *p;
    list_for_each_prev(p, &my_list) {
        struct my_data *entry = list_entry(p, struct my_data, list);
        printf("[%s, %d]->", entry->name, entry->age);
    }
    printf("\n");

    struct my_data *tmp;
    list_for_each_entry_safe(pos, tmp, &my_list, list) {
        list_del(&pos->list);  // Remove from the list
        free(pos);             // Free the element memory
    }

    return 0;
}

