#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
    int isThreaded;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->isThreaded = 0;
    return newNode;
}

// Function to insert a node into the threaded binary tree
struct Node* insertNode(struct Node* root, int data) {
    // If the tree is empty, return a new node
    if (root == NULL)
        return createNode(data);

    // Otherwise, recur down the tree
    if (data < root->data) {
        root->left = insertNode(root->left, data);
        // If the left child is NULL, make it threaded
        if (root->left->right == NULL) {
            root->left->right = root;
            root->left->isThreaded = 1;
        }
    } else if (data > root->data) {
        // If the right child is NULL, make it threaded
        if (root->right == NULL) {
            root->right = createNode(data);
            root->right->right = root->right;
            root->right->isThreaded = 1;
        } else {
            // Otherwise, recur down the tree
            root->right = insertNode(root->right, data);
        }
    }
    return root;
}

// Function to traverse the threaded binary tree in postorder
void postorderTraversal(struct Node* root) {
    if (root == NULL)
        return;

    struct Node* current = root;

    // Find the leftmost node in the tree
    while (current->left != NULL || current->right != NULL) {
        while (current->left != NULL)
            current = current->left;
        while (current->right == NULL || current->isThreaded == 1) {
            printf("%d ", current->data);
            current = current->right;
            if (current == root)
                return;
        }
        current = current->right;
    }

    // Print the root node
    printf("%d ", current->data);
}

int main() {
    struct Node* root = NULL;
    int n, data;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    printf("Enter the node values:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        root = insertNode(root, data);
    }
    printf("Postorder Traversal: ");
    postorderTraversal(root);
    printf("\n");
    return 0;
}
