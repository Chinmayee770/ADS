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
void insertNode(struct TreeNode **root, int data) {
    struct TreeNode *newNode = createNode(data);
    if (*root == NULL) {
        *root = newNode;
        return;
    }

    struct TreeNode *current = *root;
    while (1) {
        if (data <= current->data) {
            if (current->left == NULL) {
                current->left = newNode;
                return;
            }
            current = current->left;
        } else {
            if (current->right == NULL) {
                current->right = newNode;
                return;
            }
            current = current->right;
        }
    }
}

// Function to perform levelwise display of the binary search tree
void levelwiseDisplay(struct TreeNode *root) {
    if (root == NULL)
        return;

    struct TreeNode *queue[100];
    int rear = -1, front = -1;

    queue[++rear] = root;

    while (rear != front) {
        int size = rear - front;

        while (size--) {
            struct TreeNode *temp = queue[++front];
            printf("%d ", temp->data);

            if (temp->left)
                queue[++rear] = temp->left;
            if (temp->right)
                queue[++rear] = temp->right;
        }

        printf("\n");
    }
}

// Function to compute the mirror image of the binary search tree
void mirrorImage(struct TreeNode *root) {
    if (root == NULL)
        return;

    struct TreeNode *temp;

    // Swap left and right child of each node
    mirrorImage(root->left);
    mirrorImage(root->right);

    temp = root->left;
    root->left = root->right;
    root->right = temp;
}

// Function to calculate the height of the binary search tree
int height(struct TreeNode *root) {
    if (root == NULL)
        return 0;

    struct TreeNode *queue[100];
    int rear = -1, front = -1;
    int level = 0;

    queue[++rear] = root;

    while (rear != front) {
        int size = rear - front;

        while (size--) {
            struct TreeNode *temp = queue[++front];

            if (temp->left)
                queue[++rear] = temp->left;
            if (temp->right)
                queue[++rear] = temp->right;
        }

        level++;
    }

    return level;
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

int main() {
    // Input from the user to create the binary search tree
    int data, numNodes;
    struct TreeNode *root = NULL;

    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    printf("Enter the values of the nodes: ");
    for (int i = 0; i < numNodes; ++i) {
        scanf("%d", &data);
        insertNode(&root, data);
    }

    // Display the binary search tree level-wise
    printf("Levelwise display of the BST:\n");
    levelwiseDisplay(root);

    // Compute the mirror image of the binary search tree
    mirrorImage(root);
    printf("\nMirror Image of the BST:\n");
    levelwiseDisplay(root);

    // Calculate the height of the binary search tree
    printf("\nHeight of the BST: %d\n", height(root));

    // Find a key in the binary search tree
    int key;
    printf("\nEnter the key to find: ");
    scanf("%d", &key);
    struct TreeNode *foundNode = findKey(root, key);
    if (foundNode != NULL)
        printf("Key %d found in the BST.\n", key);
    else
        printf("Key %d not found in the BST.\n", key);

    return 0;
}
