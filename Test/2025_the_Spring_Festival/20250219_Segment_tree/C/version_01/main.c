#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXSIZE 100
int seg_tree[4 * 100];

typedef enum {
    OPERATION_SUM,
    OPERATION_MAX,
    OPERATION_MIN,
} E_OPERATION_TYPE;

struct ST_SEGMENT_TREE;


typedef struct ST_SEGMENT_TREE{
    int *arr;
    int size;
    int *seg_tree;
    E_OPERATION_TYPE type;

    void (*build_tree)(struct ST_SEGMENT_TREE *tree, int node, int start, int end);
    int (*range_query)(struct ST_SEGMENT_TREE *tree, int start, int end);
    void (*point_update)(struct ST_SEGMENT_TREE *tree, int idx, int newValue);
} ST_SEGMENT_TREE;

int operation_fun(E_OPERATION_TYPE type, int a, int b);
void build_tree(struct ST_SEGMENT_TREE *tree, int node, int start, int end);

int range_query(struct ST_SEGMENT_TREE *tree, int start, int end);
int range_query_internal(struct ST_SEGMENT_TREE *tree, int node, int start, int end, int l, int r);

void point_update(struct ST_SEGMENT_TREE *tree, int idx, int newValue);
void point_update_internal(struct ST_SEGMENT_TREE *tree, int node, int start, int end, int idx, int value);



int operation_fun(E_OPERATION_TYPE type, int a, int b)
{
    switch(type) {
        case OPERATION_SUM: return a + b;
        case OPERATION_MAX: return a > b ? a : b;
        case OPERATION_MIN: return a < b ? a : b;
        default: return 0;
    }
}


void build_tree(struct ST_SEGMENT_TREE *tree, int node, int start, int end)
{
    if (start == end) {
        tree->seg_tree[node] = tree->arr[start];
    } else {
        int mid = (start + end) / 2;
        int left_child  = 2 * node + 1;
        int right_child = 2 * node + 2;

        build_tree(tree, left_child, start, mid);
        build_tree(tree, right_child, mid + 1, end);

        tree->seg_tree[node] = operation_fun(tree->type, tree->seg_tree[left_child], tree->seg_tree[right_child]);
    }
}




int range_query_internal(struct ST_SEGMENT_TREE *tree, int node, int start, int end, int l, int r)
{
    if (r < start || l > end) {
        switch(tree->type) {
            case OPERATION_SUM: return 0;
            case OPERATION_MAX: return INT_MIN;         // if the no overlap, then return the INT_MIN, then this node won't be choose because to choose the MAX
            case OPERATION_MIN: return INT_MAX;         // if the no overlap, then return the INT_MAX, then this node won't be choose because to choose the MIN
        }
    }

    if (l <= start && r >= end) {
        // Total overleap
        return tree->seg_tree[node];
    }

    // Partial overleap
    int mid = (start + end) / 2;
    int left_child  = 2 * node + 1;
    int right_child = 2 * node + 2;

    int left_result = range_query_internal(tree, left_child, start, mid, l, r); 
    int right_result = range_query_internal(tree, right_child, mid + 1, end, l, r);

    // return left_sum + right_sum;
    return operation_fun(tree->type, left_result, right_result);
}


int range_query(ST_SEGMENT_TREE *tree, int left, int right)
{
    return  range_query_internal(tree, 0, 0, tree->size - 1, left, right);
}

void point_update_internal(ST_SEGMENT_TREE *tree, int node, int start, int end, int idx, int newValue)
{
    if (start == end) {
        tree->seg_tree[node] = newValue;
    } else {
        int mid = (start + end) / 2;
        int left_child  = 2 * node + 1;
        int right_child = 2 * node + 2;
        if (start <= idx && idx <= mid) { 
            point_update_internal(tree, left_child, start, mid, idx, newValue);
        } else {
            point_update_internal(tree, right_child, mid + 1, end, idx, newValue);
        }

        // seg_tree[node] = seg_tree[left_child] + seg_tree[right_child];
        tree->seg_tree[node] = operation_fun(tree->type, tree->seg_tree[left_child], tree->seg_tree[right_child]);
    }
}

void point_update(ST_SEGMENT_TREE *tree, int idx, int newValue)
{
    point_update_internal(tree, 0, 0, tree->size - 1, idx, newValue);
}

struct ST_SEGMENT_TREE* create_segment_tree(int *arr, int size, E_OPERATION_TYPE type)
{
    ST_SEGMENT_TREE *tree = (ST_SEGMENT_TREE*)malloc(sizeof(ST_SEGMENT_TREE));

    int *m_arr = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i) {
        m_arr[i] = arr[i];
    }

    tree->arr = m_arr;
    tree->size = size;
    tree->seg_tree = (int *)malloc(4 * size * sizeof(int));
    tree->type = type;

    tree->build_tree = build_tree;
    tree->range_query  = range_query;
    tree->point_update = point_update;

    tree->build_tree(tree, 0, 0, size -1);

    return tree;
}

void print_before_and_after(struct ST_SEGMENT_TREE *tree, int idx, int newValue)
{
    char *op  = "";
    switch(tree->type) {
        case OPERATION_SUM:
            op = "sum";
            break;
        case OPERATION_MAX:
            op = "max";
            break;
        case OPERATION_MIN:
            op = "min";
            break;
    }

    printf("%s of range [1, 3]: %d\n", op, tree->range_query(tree, 1, 3));
    tree->point_update(tree, idx, newValue);
    printf("%s of range [1, 3]: %d\n", op, tree->range_query(tree, 1, 3));
}


int main()
{
    int arr[] = {1, 3, 5, 7, 9, 11};
    int n = sizeof(arr) / sizeof(arr[0]);

    ST_SEGMENT_TREE *tree_sum = create_segment_tree(arr, n, OPERATION_SUM);
    ST_SEGMENT_TREE *tree_max = create_segment_tree(arr, n, OPERATION_MAX);
    ST_SEGMENT_TREE *tree_min = create_segment_tree(arr, n, OPERATION_MIN);

    print_before_and_after(tree_sum, 1, 29);
    print_before_and_after(tree_max, 1, 29);
    print_before_and_after(tree_min, 1, 29);

    return 0;
}
