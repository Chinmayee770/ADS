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

// Function to perform postorder traversal of the binary search tree non-recursively
void postorderTraversal(struct TreeNode *root) {
    if (root == NULL)
        return;

    struct TreeNode *stack1[100];
    struct TreeNode *stack2[100];
    int top1 = -1, top2 = -1;
    stack1[++top1] = root;

    while (top1 != -1) {
        struct TreeNode *current = stack1[top1--];
        stack2[++top2] = current;

        if (current->left != NULL)
            stack1[++top1] = current->left;
        if (current->right != NULL)
            stack1[++top1] = current->right;
    }

    while (top2 != -1) {
        printf("%d ", stack2[top2--]->data);
    }
}

// Function to count the total number of nodes in the binary search tree
int countNodes(struct TreeNode *root) {
    if (root == NULL)
        return 0;

    struct TreeNode *stack[100];
    int top = -1;
    int nodeCount = 0;
    stack[++top] = root;

    while (top != -1) {
        struct TreeNode *current = stack[top--];
        nodeCount++;

        if (current->right != NULL)
            stack[++top] = current->right;
        if (current->left != NULL)
            stack[++top] = current->left;
    }

    return nodeCount;
}

// Function to display leaf nodes of the binary search tree
void displayLeafNodes(struct TreeNode *root) {
    if (root == NULL)
        return;

    struct TreeNode *stack[100];
    int top = -1;
    stack[++top] = root;

    while (top != -1) {
        struct TreeNode *current = stack[top--];

        if (current->left == NULL && current->right == NULL)
            printf("%d ", current->data);

        if (current->right != NULL)
            stack[++top] = current->right;
        if (current->left != NULL)
            stack[++top] = current->left;
    }
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

    printf("BST in Postorder way: ");
    postorderTraversal(root);
    printf("\n");

    printf("Total number of nodes in the BST: %d\n", countNodes(root));

    printf("Leaf nodes of the BST: ");
    displayLeafNodes(root);
    printf("\n");

    return 0;
}
