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

// Function to traverse the threaded binary tree in Inorder way
void inorderTraversal(struct Node *root) {
    struct Node *current = root;
    while (current != NULL) {
        // Find the leftmost node in the subtree
        while (current->left != NULL)
            current = current->left;
        
        // Print the current node
        printf("%d ", current->data);

        // If the right pointer is a thread, move to the successor
        if (current->isThreaded)
            current = current->right;
        else { // Otherwise, move to the leftmost node in the right subtree
            current = current->right;
            while (current != NULL && !current->isThreaded)
                current = current->left;
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

    printf("\nInorder Traversal of Threaded Binary Tree: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
