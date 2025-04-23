#include <stdio.h>
#include <stdlib.h>

#define MIN_DEGREE 3  // Minimum degree (defines the range for number of keys)

typedef struct BTreeNode {
    int *keys;
    struct BTreeNode **children;
    int numKeys;
    int isLeaf;
} BTreeNode;

typedef struct BTree {
    BTreeNode *root;
} BTree;

// Function prototypes
BTreeNode* createNode(int isLeaf);
void traverse(BTreeNode* node);
BTreeNode* search(BTreeNode* node, int key);
void insert(BTree* tree, int key);
void insertNonFull(BTreeNode* node, int key);
void splitChild(BTreeNode* parent, int index, BTreeNode* child);
void initBTree(BTree* tree);

int main() {
    BTree tree;
    initBTree(&tree);  // Initialize the B-tree

    // Inserting values into the B-tree
    insert(&tree, 10);
    insert(&tree, 20);
    insert(&tree, 5);
    insert(&tree, 6);
    insert(&tree, 12);
    insert(&tree, 30);
    insert(&tree, 7);
    insert(&tree, 17);

    // Traversing the tree
    printf("B-tree traversal: ");
    traverse(tree.root);
    printf("\n");

    // Searching for a key
    int key = 12;
    BTreeNode *result = search(tree.root, key);
    if (result != NULL) {
        printf("Key %d found in the B-tree!\n", key);
    } else {
        printf("Key %d not found in the B-tree.\n", key);
    }

    return 0;
}

// Function to initialize the B-tree
void initBTree(BTree* tree) {
    tree->root = createNode(1);  // Root node is a leaf initially
}

// Function to create a new B-tree node
BTreeNode* createNode(int isLeaf) {
    BTreeNode *node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->keys = (int*)malloc((2 * MIN_DEGREE - 1) * sizeof(int));
    node->children = (BTreeNode**)malloc(2 * MIN_DEGREE * sizeof(BTreeNode*));
    node->numKeys = 0;
    node->isLeaf = isLeaf;
    return node;
}

// Function to traverse the B-tree
void traverse(BTreeNode* node) {
    if (node != NULL) {
        int i;
        for (i = 0; i < node->numKeys; i++) {
            if (!node->isLeaf) {
                traverse(node->children[i]);
            }
            printf("%d ", node->keys[i]);
        }
        if (!node->isLeaf) {
            traverse(node->children[i]);
        }
    }
}

// Function to search a key in the B-tree
BTreeNode* search(BTreeNode* node, int key) {
    int i = 0;
    while (i < node->numKeys && key > node->keys[i]) {
        i++;
    }
    if (i < node->numKeys && node->keys[i] == key) {
        return node;  // Key found
    }
    if (node->isLeaf) {
        return NULL;  // Key not found
    }
    return search(node->children[i], key);  // Search in the appropriate child
}

// Function to insert a key into the B-tree
void insert(BTree* tree, int key) {
    BTreeNode* root = tree->root;
    if (root->numKeys == 2 * MIN_DEGREE - 1) {
        BTreeNode* newNode = createNode(0);
        newNode->children[0] = root;
        tree->root = newNode;
        splitChild(newNode, 0, root);
        insertNonFull(newNode, key);
    } else {
        insertNonFull(root, key);
    }
}

// Function to insert a key into a node that is not full
void insertNonFull(BTreeNode* node, int key) {
    int i = node->numKeys - 1;
    if (node->isLeaf) {
        while (i >= 0 && node->keys[i] > key) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->numKeys++;
    } else {
        while (i >= 0 && node->keys[i] > key) {
            i--;
        }
        i++;
        if (node->children[i]->numKeys == 2 * MIN_DEGREE - 1) {
            splitChild(node, i, node->children[i]);
            if (node->keys[i] < key) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

// Function to split a child node
void splitChild(BTreeNode* parent, int index, BTreeNode* child) {
    BTreeNode* newNode = createNode(child->isLeaf);
    newNode->numKeys = MIN_DEGREE - 1;
    
    for (int i = 0; i < MIN_DEGREE - 1; i++) {
        newNode->keys[i] = child->keys[i + MIN_DEGREE];
    }

    if (!child->isLeaf) {
        for (int i = 0; i < MIN_DEGREE; i++) {
            newNode->children[i] = child->children[i + MIN_DEGREE];
        }
    }

    child->numKeys = MIN_DEGREE - 1;
    
    for (int i = parent->numKeys; i > index; i--) {
        parent->children[i + 1] = parent->children[i];
    }

    parent->children[index + 1] = newNode;

    for (int i = parent->numKeys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }

    parent->keys[index] = child->keys[MIN_DEGREE - 1];
    parent->numKeys++;
}
