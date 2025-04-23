#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Define a generic operation function type
typedef void* (*OperationFunc)(void*, void*);

// Define a struct to represent the Segment Tree
typedef struct {
    void* tree;          // Array to store the segment tree
    int n;               // Size of the input array
    size_t data_size;    // Size of the data type (e.g., sizeof(int), sizeof(float), etc.)
    OperationFunc operation; // Function pointer for the operation (e.g., min, sum, max)
    void* identity;      // Identity value for the operation (e.g., INT_MAX for min, 0 for sum)
} SegmentTree;

// Function to create a new Segment Tree
SegmentTree* create_segment_tree(void* arr, int n, size_t data_size, OperationFunc operation, void* identity) {
    SegmentTree* st = (SegmentTree*)malloc(sizeof(SegmentTree));
    st->n = n;
    st->data_size = data_size;
    st->operation = operation;
    st->identity = malloc(data_size);
    memcpy(st->identity, identity, data_size); // Copy the identity value

    // Allocate memory for the segment tree
    st->tree = malloc(4 * n * data_size);

    // Build the segment tree
    // (Implementation of build function is provided below)
    build_segment_tree(st, arr, 0, 0, n - 1);

    return st;
}

// Function to free the Segment Tree
void free_segment_tree(SegmentTree* st) {
    free(st->tree);
    free(st->identity);
    free(st);
}

// Function to build the segment tree
void build_segment_tree(SegmentTree* st, void* arr, int node, int start, int end) {
    if (start == end) {
        // Leaf node: copy the value from the input array
        // tree[node] = arr[start]
        memcpy((char*)st->tree + node * st->data_size, (char*)arr + start * st->data_size, st->data_size);
    } else {
        int mid = (start + end) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;

        // Recursively build the left and right subtrees
        build_segment_tree(st, arr, left_child, start, mid);
        build_segment_tree(st, arr, right_child, mid + 1, end);

        // Combine the results of the left and right subtrees using the operation function
        void* left_result = (char*)st->tree + left_child * st->data_size;
        void* right_result = (char*)st->tree + right_child * st->data_size;
        void* result = st->operation(left_result, right_result);

        // Store the result in the current node
        memcpy((char*)st->tree + node * st->data_size, result, st->data_size);
        free(result); // Free the dynamically allocated result
    }
}

// Function to query the segment tree
void* query_segment_tree(SegmentTree* st, int node, int start, int end, int L, int R) {
    // If the current range is completely outside the query range
    if (R < start || end < L) {
        return st->identity; // Return the identity value
    }

    // If the current range is completely inside the query range
    if (L <= start && end <= R) {
        return (char*)st->tree + node * st->data_size;
    }

    // Otherwise, partially inside and outside
    int mid = (start + end) / 2;
    int left_child = 2 * node + 1;
    int right_child = 2 * node + 2;

    void* left_result = query_segment_tree(st, left_child, start, mid, L, R);
    void* right_result = query_segment_tree(st, right_child, mid + 1, end, L, R);

    // Combine the results of the left and right subtrees using the operation function
    return st->operation(left_result, right_result);
}

// Example operation functions
void* min_int(void* a, void* b) {
    int* result = (int*)malloc(sizeof(int));
    *result = (*(int*)a < *(int*)b) ? *(int*)a : *(int*)b;
    return result;
}

void* sum_int(void* a, void* b) {
    int* result = (int*)malloc(sizeof(int));
    *result = *(int*)a + *(int*)b;
    return result;
}

void* max_int(void* a, void* b) {
    int* result = (int*)malloc(sizeof(int));
    *result = (*(int*)a > *(int*)b) ? *(int*)a : *(int*)b;
    return result;
}

// Identity values
int int_max_identity() {
    return INT_MAX;
}

int int_zero_identity() {
    return 0;
}

int int_min_identity() {
    return INT_MIN;
}

int main() {
    // Example with integers
    int arr_int[] = {1, 3, 5, 7, 9, 11};
    int n_int = sizeof(arr_int) / sizeof(arr_int[0]);

    // Create Segment Tree for Min
    int min_identity = int_max_identity();
    SegmentTree* st_min = create_segment_tree(arr_int, n_int, sizeof(int), (OperationFunc)min_int, &min_identity);

    // Create Segment Tree for Sum
    int sum_identity = int_zero_identity();
    SegmentTree* st_sum = create_segment_tree(arr_int, n_int, sizeof(int), (OperationFunc)sum_int, &sum_identity);

    // Create Segment Tree for Max
    int max_identity = int_min_identity();
    SegmentTree* st_max = create_segment_tree(arr_int, n_int, sizeof(int), (OperationFunc)max_int, &max_identity);

    // Query examples
    int* min_result = (int*)query_segment_tree(st_min, 0, 0, n_int - 1, 1, 4);
    printf("Min in range [1, 4]: %d\n", *min_result);
    free(min_result);

    int* sum_result = (int*)query_segment_tree(st_sum, 0, 0, n_int - 1, 1, 4);
    printf("Sum in range [1, 4]: %d\n", *sum_result);
    free(sum_result);

    int* max_result = (int*)query_segment_tree(st_max, 0, 0, n_int - 1, 1, 4);
    printf("Max in range [1, 4]: %d\n", *max_result);
    free(max_result);

    // Free memory
    free_segment_tree(st_min);
    free_segment_tree(st_sum);
    free_segment_tree(st_max);

    return 0;
}
