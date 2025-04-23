#include <stdio.h>
#include <stdlib.h>

typedef struct ST_Node{
    int value;
    struct ST_Node *left;
    struct ST_Node *right;
    int height;
} ST_Node;

typedef enum {
    TRAVERSAL_IN_ORDER = 1,
    TRAVERSAL_PRE_ORDER = 2,
    TRAVERSAL_POST_ORDER = 3,
    TRAVERSAL_LEVEL_ORDER = 4,
} E_TRAVERSAL_TYPE;


int max(int a, int b);


ST_Node* newNode(int value);

int getHeight(ST_Node *node);
int getBalance(ST_Node *node);
ST_Node*  leftRotate(ST_Node *node);
ST_Node* rightRotate(ST_Node *node);

ST_Node* insert(ST_Node *root, int data);
ST_Node* search(ST_Node *root, int data);
ST_Node* delete(int data);

void traversal_InOrder(ST_Node *root);
void traversal_PreOrder(ST_Node *root);
void traversal_PostOrder(ST_Node *root);
void traversal_LevelOrder(ST_Node *root);
void traversal(ST_Node *root, E_TRAVERSAL_TYPE type);



int main()
{
    ST_Node *root = newNode(20);
    root = insert(root, 10);
    root = insert(root, 8);
    root = insert(root, 6);
    root = insert(root, 7);
    
    printf("%d\n", root->value);
    printf("%d\n", root->left->value);
    printf("%d\n", root->right->value);
    printf("%d\n", root->left->left->value);
    printf("%d\n", root->left->right->value);
    traversal(root, TRAVERSAL_IN_ORDER);

    printf("%d\n", root->value);
    printf("%d\n", root->left->value);
    printf("%d\n", root->right->value);
    printf("%d\n", root->left->left->value);
    printf("%d\n", root->left->right->value);
    traversal(root, TRAVERSAL_PRE_ORDER);
    
    printf("%d\n", root->value);
    printf("%d\n", root->left->value);
    printf("%d\n", root->right->value);
    printf("%d\n", root->left->left->value);
    printf("%d\n", root->left->right->value);
    traversal(root, TRAVERSAL_POST_ORDER);

    printf("%d\n", root->value);
    printf("%d\n", root->left->value);
    printf("%d\n", root->right->value);
    printf("%d\n", root->left->left->value);
    printf("%d\n", root->left->right->value);
    traversal(root, TRAVERSAL_LEVEL_ORDER);

    ST_Node *target = search(root, 7);
    printf("%d\n", target->left->value);
    printf("%d\n", target->right->value);

    return 0;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

ST_Node* newNode(int value)
{
    ST_Node *newNode = (ST_Node*)malloc(sizeof(ST_Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;

    return newNode;
}

int getHeight(ST_Node *node)
{
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

ST_Node* rightRotate(ST_Node *node)
{
    ST_Node *Mid = node->left;
    ST_Node *tmp = Mid->right;

    Mid->right = node;
    node->left = tmp;



    Mid->height = max(getHeight(Mid->left), getHeight(Mid->right)) + 1;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    return Mid;
}

ST_Node* leftRotate(ST_Node *node)
{
    ST_Node *Mid = node->right;
    ST_Node *tmp = Mid->left;

    Mid->left = node;
    node->right = tmp;

    Mid->height = max(getHeight(Mid->left), getHeight(Mid->right)) + 1;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    return Mid;
}


int getBalance(ST_Node *node)
{
    if (node == NULL) {
        return 0;
    }

    return getHeight(node->left) - getHeight(node->right);
}

ST_Node* insert(ST_Node *node, int data)
{
    if (node == NULL) {
        return newNode(data);
    }


    if (data > node->value) {
        node->right = insert(node->right, data);
    } else if (data < node->value) {
        node->left = insert(node->left, data);
    } else {
        return node;
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && data < node->left->value) {
        return rightRotate(node);
    }

    if (balance < -1 && data > node->right->value) {
        return leftRotate(node);
    }

    if (balance > 1 && data > node->left->value) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && data < node->right->value) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

ST_Node* search(ST_Node *root, int data)
{
    if (root == NULL | root->value == data) {
        return root;
    }

    if (data < root->value) {
        return search(root->left, data);
    } else {
        return search(root->right, data);
    }
}



void traversal_InOrder(ST_Node *root)
{
    if (root != NULL) {
        traversal_InOrder(root->left);
        printf("%d ", root->value);
        traversal_InOrder(root->right);
    }

}

void traversal_PreOrder(ST_Node *root)
{
    if (root != NULL) {
       printf("%d ", root->value);
       traversal_PreOrder(root->left);
       traversal_PreOrder(root->right);
    }
}

void traversal_PostOrder(ST_Node *root)
{
    if (root != NULL) {
       traversal_PostOrder(root->left);
       traversal_PostOrder(root->right);
       printf("%d ", root->value);
    }
}

void traversal_LevelOrder(ST_Node *root)
{

    if (root == NULL) {
        return;
    }

    ST_Node** queue = (ST_Node**)malloc(sizeof(ST_Node*) * 1000);

    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        ST_Node* currentNode = queue[front++];
        printf("%d ", currentNode->value);

        if (currentNode->left != NULL) {
            queue[rear++] = currentNode->left;
        }

        if (currentNode->right != NULL) {
            queue[rear++] = currentNode->right;
        }
    }

    free(queue);
}

void traversal(ST_Node *root, E_TRAVERSAL_TYPE type)
{
    switch(type)  {
        case TRAVERSAL_IN_ORDER:
            traversal_InOrder(root);
            break;
        case TRAVERSAL_PRE_ORDER:
            traversal_PreOrder(root);
            break;
        case TRAVERSAL_POST_ORDER:
            traversal_PostOrder(root);
            break;
        case TRAVERSAL_LEVEL_ORDER:
            traversal_LevelOrder(root);
            break;
        default:
            traversal_InOrder(root);
            break;
    }
    printf("\n");
}
        



