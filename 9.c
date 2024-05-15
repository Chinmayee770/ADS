#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in BST
struct TreeNode {
    int key;
    struct TreeNode *left, *right;
};

// Function to create a new BST node
struct TreeNode *newNode(int item) {
    struct TreeNode *temp = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to insert a new key in BST
struct TreeNode *insert(struct TreeNode *node, int key) {
    // If the tree is empty, return a new node
    if (node == NULL) return newNode(key);
    
    // Otherwise, recur down the tree
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    
    // Return the (unchanged) node pointer
    return node;
}

// Function to find the node with minimum key value
struct TreeNode *minValueNode(struct TreeNode *node) {
    struct TreeNode *current = node;
    
    // Loop down to find the leftmost leaf
    while (current && current->left != NULL)
        current = current->left;
    
    return current;
}

// Function to delete the node with given key and return the new root
struct TreeNode *deleteNode(struct TreeNode *root, int key) {
    // Base case
    if (root == NULL) return root;
    
    // Recur down the tree
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct TreeNode *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct TreeNode *temp = root->left;
            free(root);
            return temp;
        }
        
        // Node with two children: Get the inorder successor (smallest in the right subtree)
        struct TreeNode *temp = minValueNode(root->right);
        
        // Copy the inorder successor's content to this node
        root->key = temp->key;
        
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Function to print level order traversal of BST
void printLevelOrder(struct TreeNode *root) {
    if (root == NULL) return;
    
    // Create an empty queue for level order traversal
    struct TreeNode *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;
    
    while (front < rear) {
        struct TreeNode *node = queue[front++];
        printf("%d ", node->key);
        
        // Enqueue left child
        if (node->left != NULL)
            queue[rear++] = node->left;
        
        // Enqueue right child
        if (node->right != NULL)
            queue[rear++] = node->right;
    }
}

// Function to build BST
struct TreeNode *buildBST() {
    struct TreeNode *root = NULL;
    char input[20];
    int val;
    while (1) {
        printf("Enter a value to insert into the BST (or type 'done' to finish): ");
        scanf("%s", input);
        if (strcmp(input, "done") == 0)
            break;
        else {
            val = atoi(input);
            root = insert(root, val);
        }
    }
    return root;
}

// Function to delete from BST
struct TreeNode *deleteFromBST(struct TreeNode *root) {
    char input[20];
    int val;
    while (1) {
        printf("Enter a value to delete from the BST (or type 'done' to finish): ");
        scanf("%s", input);
        if (strcmp(input, "done") == 0)
            break;
        else {
            val = atoi(input);
            root = deleteNode(root, val);
            printf("Node with value %d deleted.\n", val);
        }
    }
    return root;
}

// Main function
int main() {
    struct TreeNode *root = NULL;
    printf("Building Binary Search Tree:\n");
    root = buildBST();
    
    printf("\nBST Level-wise:\n");
    printLevelOrder(root);
    
    printf("\n\nDeleting nodes from BST:\n");
    root = deleteFromBST(root);
    
    printf("\nBST after deletion Level-wise:\n");
    printLevelOrder(root);
    
    return 0;
}
