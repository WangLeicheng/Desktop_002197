#include <iostream>
#include <climits>
#include <algorithm>
#include <string>
#include <limits>  // Add this header for numeric_limits

using namespace std;

// Template class for the Segment Tree with multiple operations (min, sum, max)
template <typename T, typename Op>
class SegmentTree {
private:
    T* tree;
    int n;
    Op operation;  // Function object for combining nodes

    // Build the segment tree
    void build(T arr[], int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            int left_child = 2 * node + 1;
            int right_child = 2 * node + 2;

            build(arr, left_child, start, mid);      // Left child
            build(arr, right_child, mid + 1, end);   // Right child

            tree[node] = operation(tree[left_child], tree[right_child]);
        }
    }

    // Range query operation
    T query(int node, int start, int end, int L, int R) {
        // If the current range is completely outside the query range
        if (R < start || end < L) {
            return operation.template identity<T>();  // Explicitly pass type T to identity()
        }
        // If the current range is completely inside the query range
        if (L <= start && end <= R) {
            return tree[node];
        }

        // Otherwise, partially inside and outside
        int mid = (start + end) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;

        T left_result = query(left_child, start, mid, L, R);
        T right_result = query(right_child, mid + 1, end, L, R);

        return operation(left_result, right_result);
    }

    // Update a value in the segment tree
    void update(int node, int start, int end, int idx, T value) {
        if (start == end) {
            tree[node] = value;
        } else {
            int mid = (start + end) / 2;
            int left_child = 2 * node + 1;
            int right_child = 2 * node + 2;

            if (idx <= mid) {
                update(left_child, start, mid, idx, value);
            } else {
                update(right_child, mid + 1, end, idx, value);
            }

            tree[node] = operation(tree[left_child], tree[right_child]);
        }
    }

public:
    // Constructor to initialize the segment tree
    SegmentTree(T arr[], int size, Op op) {
        n = size;
        tree = new T[4 * n];  // Allocate memory for the segment tree
        operation = op;
        build(arr, 0, 0, n - 1);
    }

    // Destructor to free allocated memory
    ~SegmentTree() {
        delete[] tree;
    }

    // Query function to get the result of the operation in range [L, R]
    T query(int L, int R) {
        return query(0, 0, n - 1, L, R);
    }

    // Update function to set a value at index idx
    void update(int idx, T value) {
        update(0, 0, n - 1, idx, value);
    }
};

// Function object for min operation
struct MinOp {
    int operator()(int a, int b) const {
        return min(a, b);
    }

    float operator()(float a, float b) const {
        return min(a, b);
    }

    string operator()(string a, string b) const {
        return min(a, b);
    }

    // Identity value for min is the largest possible value
    template <typename T>
    T identity() const {
        return numeric_limits<T>::max();  // Correctly use template type T
    }
};

// Function object for sum operation
struct SumOp {
    int operator()(int a, int b) const {
        return a + b;
    }

    float operator()(float a, float b) const {
        return a + b;
    }

    string operator()(string a, string b) const {
        return "";  // Sum operation for strings doesn't make sense, can be ignored for this case
    }

    // Identity value for sum is 0
    template <typename T>
    T identity() const {
        return T(0);
    }
};

// Function object for max operation
struct MaxOp {
    int operator()(int a, int b) const {
        return max(a, b);
    }

    float operator()(float a, float b) const {
        return max(a, b);
    }

    string operator()(string a, string b) const {
        return max(a, b);
    }

    // Identity value for max is the smallest possible value
    template <typename T>
    T identity() const {
        return numeric_limits<T>::lowest();
    }
};

struct MulOp {
    int operator()(int a, int b) const {
        return a * b;
    }

    float operator()(float a, float b) const {
        return a * b;
    }

    string operator()(string a, string b) const {
        return a;
    }

    template <typename T> 
    T identity() const {
        return  T(0);
    }
};


int main() {
    // Example with integers (Min, Sum, Max)
    int arr_int[] = {1, 3, 2, 7, 9, 11};
    int n_int = sizeof(arr_int) / sizeof(arr_int[0]);

    // Segment Tree for Min
    SegmentTree<int, MinOp> seg_tree_min(arr_int, n_int, MinOp());
    cout << "Min in range [1, 4]: " << seg_tree_min.query(1, 4) << endl;

    // Segment Tree for Sum
    SegmentTree<int, SumOp> seg_tree_sum(arr_int, n_int, SumOp());
    cout << "Sum in range [1, 4]: " << seg_tree_sum.query(1, 4) << endl;

    // Segment Tree for Max
    SegmentTree<int, MaxOp> seg_tree_max(arr_int, n_int, MaxOp());
    cout << "Max in range [1, 4]: " << seg_tree_max.query(1, 4) << endl;

    // Update value in array and query again
    seg_tree_min.update(3, 0);
    cout << "Min in range [1, 4] after update: " << seg_tree_min.query(1, 4) << endl;

    // Example with strings (Min operation only)
    string arr_str[] = {"apple", "banana", "cherry", "date", "elderberry", "fig"};
    int n_str = sizeof(arr_str) / sizeof(arr_str[0]);

    // Segment Tree for Min (lexicographical)
    SegmentTree<string, MinOp> seg_tree_str(arr_str, n_str, MinOp());
    cout << "Lexicographically smallest string in range [1, 4]: " << seg_tree_str.query(1, 4) << endl;

    SegmentTree<int, MulOp> seg_tree_mul(arr_int, n_int, MulOp());
    cout << "Mul in range [1, 4]: " << seg_tree_mul.query(1, 4) << endl;

    return 0;
}

