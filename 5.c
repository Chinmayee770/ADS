#include <stdio.h>
#include <stdlib.h>

// Structure for BST node
struct TreeNode {
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function to create a new BST node
struct TreeNode *newNode(int item) {
    struct TreeNode *temp = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to insert a key into BST
struct TreeNode *insert(struct TreeNode *node, int key) {
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    return node;
}

// Function to print post-order traversal of BST without recursion
void postOrder(struct TreeNode *root) {
    if (root == NULL)
        return;

    struct TreeNode *stack[100];
    int top = -1;

    do {
        // Move to leftmost node
        while (root) {
            // Push right child's root and then root to stack
            if (root->right)
                stack[++top] = root->right;
            stack[++top] = root;
            root = root->left;
        }

        // Pop an item from stack and set it as root
        root = stack[top--];

        // If the popped item has a right child and the right child is at top of stack, then remove the right child from stack,
        // push the root back and set root as the right child
        if (root->right && stack[top] == root->right) {
            stack[top--] = root;
            root = root->right;
        } else {
            printf("%d ", root->key);
            root = NULL;
        }
    } while (top >= 0);
}

// Function to find a key in BST
struct TreeNode *find(struct TreeNode *root, int key) {
    while (root != NULL) {
        if (key < root->key)
            root = root->left;
        else if (key > root->key)
            root = root->right;
        else
            return root;
    }
    return NULL;
}

// Function to get mirror image of BST
struct TreeNode *mirror(struct TreeNode *node) {
    if (node == NULL)
        return NULL;
    
    struct TreeNode *temp = node->left;
    node->left = mirror(node->right);
    node->right = mirror(temp);

    return node;
}

// Function to display menu
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Insert\n");
    printf("2. Mirror Image\n");
    printf("3. Find\n");
    printf("4. Post-order Traversal (Non-recursive)\n");
    printf("5. Exit\n");
}

// Main function
int main() {
    struct TreeNode *root = NULL;
    int choice, key;

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                root = mirror(root);
                printf("Mirror image created.\n");
                break;
            case 3:
                printf("Enter key to find: ");
                scanf("%d", &key);
                if (find(root, key) != NULL)
                    printf("Key %d found.\n", key);
                else
                    printf("Key %d not found.\n", key);
                break;
            case 4:
                printf("Post-order Traversal (Non-recursive): ");
                postOrder(root);
                printf("\n");
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 5);

    return 0;
}
