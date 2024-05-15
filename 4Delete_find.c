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

// Function to find the minimum value node in a BST
struct TreeNode *minValueNode(struct TreeNode *node) {
    struct TreeNode *current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a node with given key from the BST
struct TreeNode *deleteNode(struct TreeNode *root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct TreeNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct TreeNode *temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct TreeNode *temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        root->data = temp->data;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to find a key in the binary search tree
struct TreeNode *findKey(struct TreeNode *root, int key) {
    while (root != NULL) {
        if (key < root->data)
            root = root->left;
        else if (key > root->data)
            root = root->right;
        else
            return root;
    }
    return NULL; // Key not found
}

// Function to perform inorder traversal of the binary search tree
void inorderTraversal(struct TreeNode *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
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

    printf("BST in Inorder way: ");
    inorderTraversal(root);
    printf("\n");

    printf("Enter the key to delete from the BST (-1 to stop):\n");
    do {
        scanf("%d", &key);
        if (key != -1)
            root = deleteNode(root, key);
    } while (key != -1);

    printf("BST after deletion in Inorder way: ");
    inorderTraversal(root);
    printf("\n");

    printf("Enter the key to find in the BST (-1 to stop):\n");
    do {
        scanf("%d", &key);
        if (key != -1) {
            if (findKey(root, key) != NULL)
                printf("Key %d found in the BST.\n", key);
            else
                printf("Key %d not found in the BST.\n", key);
        }
    } while (key != -1);

    return 0;
}
