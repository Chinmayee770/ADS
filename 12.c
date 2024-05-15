#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the threaded binary tree
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    int isThreaded; // Flag to indicate whether right pointer is a thread or not
};

// Function to create a new node
struct Node *createNode(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->isThreaded = 0; // By default, right pointer is not a thread
    return newNode;
}

// Function to perform Inorder threading of the binary tree
void createThreaded(struct Node *root, struct Node **prev) {
    if (root == NULL) return;

    // Recur for left subtree
    createThreaded(root->left, prev);

    // If the previous node exists and its right pointer is null,
    // make it point to the current node and set the threaded flag
    if (*prev != NULL && (*prev)->right == NULL) {
        (*prev)->right = root;
        (*prev)->isThreaded = 1;
    }

    // Update the previous node
    *prev = root;

    // Recur for right subtree
    createThreaded(root->right, prev);
}

// Function to traverse the threaded binary tree in Preorder way
void preorderTraversal(struct Node *root) {
    while (root != NULL) {
        printf("%d ", root->data); // Print the current node
        if (!root->left) { // If left child is null, move to the right child
            root = root->right;
        } else { // If left child exists, find the rightmost child of the left subtree
            struct Node *temp = root->left;
            while (temp->right && temp->right != root)
                temp = temp->right;
            if (!temp->right) { // If right pointer of rightmost child is null, thread it to the current node
                temp->right = root;
                root = root->left;
            } else { // If right pointer of rightmost child is already threaded, revert the thread and move to the right child
                temp->right = NULL;
                root = root->right;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of nodes in the binary tree: ");
    scanf("%d", &n);

    struct Node *root = NULL;
    struct Node *prev = NULL;

    printf("Enter the values of the nodes:\n");
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        struct Node *newNode = createNode(val);

        if (root == NULL) // If tree is empty, set the new node as root
            root = newNode;
        else // Otherwise, insert the new node into the tree
            createThreaded(newNode, &prev);

        prev = newNode; // Update the previous node
    }

    printf("\nPreorder Traversal of Threaded Binary Tree: ");
    preorderTraversal(root);
    printf("\n");

    return 0;
}
