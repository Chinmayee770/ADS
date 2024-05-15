#include <stdio.h>
#include <stdlib.h>

// Define the structure of a binary search tree node
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function to create a new node
struct TreeNode *createNode(int data) {
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the binary search tree
struct TreeNode *insertNode(struct TreeNode *root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insertNode(root->left, data);
    else if (data > root->data)
        root->right = insertNode(root->right, data);

    return root;
}

// Function to perform preorder traversal of the binary search tree non-recursively
void preorderTraversal(struct TreeNode *root) {
    if (root == NULL)
        return;

    struct TreeNode *stack[100];
    int top = -1;
    stack[++top] = root;

    while (top != -1) {
        struct TreeNode *current = stack[top--];
        printf("%d ", current->data);

        if (current->right != NULL)
            stack[++top] = current->right;
        if (current->left != NULL)
            stack[++top] = current->left;
    }
}

// Function to perform inorder traversal of the binary search tree non-recursively
void inorderTraversal(struct TreeNode *root) {
    if (root == NULL)
        return;

    struct TreeNode *stack[100];
    int top = -1;
    struct TreeNode *current = root;

    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }

        current = stack[top--];
        printf("%d ", current->data);

        current = current->right;
    }
}

// Function to count the number of leaf nodes in the binary search tree
int countLeafNodes(struct TreeNode *root) {
    if (root == NULL)
        return 0;

    struct TreeNode *stack[100];
    int top = -1;
    int leafCount = 0;
    stack[++top] = root;

    while (top != -1) {
        struct TreeNode *current = stack[top--];

        if (current->left == NULL && current->right == NULL)
            leafCount++;

        if (current->right != NULL)
            stack[++top] = current->right;
        if (current->left != NULL)
            stack[++top] = current->left;
    }

    return leafCount;
}

// Function to compute the mirror image of the binary search tree
void mirrorImage(struct TreeNode *root) {
    if (root == NULL)
        return;

    struct TreeNode *temp = root->left;
    root->left = root->right;
    root->right = temp;

    mirrorImage(root->left);
    mirrorImage(root->right);
}

int main() {
    struct TreeNode *root = NULL;
    int choice, key;

    printf("Enter the keys to insert into the BST (-1 to stop):\n");
    do {
        scanf("%d", &key);
        if (key != -1)
            root = insertNode(root, key);
    } while (key != -1);

    printf("BST in Preorder way: ");
    preorderTraversal(root);
    printf("\n");

    printf("BST in Inorder way: ");
    inorderTraversal(root);
    printf("\n");

    printf("Number of leaf nodes in the BST: %d\n", countLeafNodes(root));

    printf("Computing mirror image of the BST...\n");
    mirrorImage(root);
    printf("Mirror image computed.\n");

    printf("BST in Preorder way after mirror image: ");
    preorderTraversal(root);
    printf("\n");

    return 0;
}
