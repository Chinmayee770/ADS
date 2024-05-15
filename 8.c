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

// Function to find the minimum value node in a binary search tree
struct TreeNode *minValueNode(struct TreeNode *node) {
    struct TreeNode *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a node from the binary search tree
struct TreeNode *deleteNode(struct TreeNode *root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct TreeNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct TreeNode *temp = root->left;
            free(root);
            return temp;
        }

        struct TreeNode *temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
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

int main() {
    struct TreeNode *root = NULL;
    int choice, key;

    printf("Enter the keys to insert into the BST (-1 to stop):\n");
    do {
        scanf("%d", &key);
        if (key != -1)
            root = insertNode(root, key);
    } while (key != -1);

    printf("BST in Non-recursive Postorder way: ");
    postorderTraversal(root);
    printf("\n");

    printf("Enter the key to delete from the BST: ");
    scanf("%d", &key);
    root = deleteNode(root, key);
    
    printf("BST after deletion in Non-recursive Postorder way: ");
    postorderTraversal(root);
    printf("\n");

    return 0;
}
