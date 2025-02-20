#include <stdio.h>

#define MAXSIZE 100

int seg_tree[4 * 100];


void build_tree(int arr[], int node, int start, int end)
{
    if (start == end) {
        seg_tree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        int left_child  = 2 * node + 1;
        int right_child = 2 * node + 2;

        build_tree(arr, left_child, start, mid);
        build_tree(arr, right_child, mid + 1, end);

        seg_tree[node] = seg_tree[left_child] + seg_tree[right_child];
    }
}

int range_query(int node, int start, int end, int l, int r)
{
    if (r < start || l > end) {
        // No overleap
        return 0;
    }

    if (l <= start && r >= end) {
        // Total overleap
        return seg_tree[node];
    }

    // Partial overleap
    int mid = (start + end) / 2;
    int left_child  = 2 * node + 1;
    int right_child = 2 * node + 2;

    int left_sum = range_query(left_child, start, mid, l, r); 
    int right_sum = range_query(right_child, mid + 1, end, l, r);

    return left_sum + right_sum;
}

void point_update(int node, int start, int end, int idx, int value)
{
    if (start == end) {
        seg_tree[node] = value;
    } else {
        int mid = (start + end) / 2;
        int left_child  = 2 * node + 1;
        int right_child = 2 * node + 2;
        if (start <= idx && idx <= mid) { 
            point_update(left_child, start, end, idx, value);
        } else {
            point_update(right_child, start, end, idx, value);
        }

        seg_tree[node] = seg_tree[left_child] + seg_tree[right_child];
    }
}


int main()
{
    int arr[] = {1, 3, 5, 7, 9, 11};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("arr numbers = %d\n", n);

    build_tree(arr, 0, 0, n - 1);

    //for (int i = 0; i < n; ++i) {
    //     printf("%d\n", seg_tree[i]);
    // }


    printf("Sum of range [1, 3]: %d\n", range_query(0, 0, n - 1, 1, 3));
       
    return 0;
}
