#include <stdio.h>
#include <stdlib.h>

// AVL Tree Node
struct TreeNode {
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
    int height;
};

// Function to create a new AVL tree node
struct TreeNode *newNode(int key) {
    struct TreeNode *node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Function to get height of a node
int height(struct TreeNode *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to get maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to perform a right rotation
struct TreeNode *rightRotate(struct TreeNode *y) {
    struct TreeNode *x = y->left;
    struct TreeNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Function to perform a left rotation
struct TreeNode *leftRotate(struct TreeNode *x) {
    struct TreeNode *y = x->right;
    struct TreeNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Get balance factor of a node
int getBalance(struct TreeNode *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Function to insert a key into AVL tree
struct TreeNode *insert(struct TreeNode *node, int key) {
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // Duplicate keys not allowed

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Function to display inorder traversal of AVL tree
void inorder(struct TreeNode *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Function to take input from user and build AVL tree
struct TreeNode *buildAVLTree() {
    struct TreeNode *root = NULL;
    int key;
    char ch;

    do {
        printf("Enter key to insert: ");
        scanf("%d", &key);
        root = insert(root, key);

        printf("Do you want to insert another key? (y/n): ");
        scanf(" %c", &ch);
    } while (ch == 'y' || ch == 'Y');

    return root;
}

// Main function
int main() {
    struct TreeNode *root = NULL;

    printf("Enter keys to insert into AVL tree. Enter any character to stop.\n");
    root = buildAVLTree();

    printf("Sorted AVL Tree: ");
    inorder(root);
    printf("\n");

    return 0;
}
