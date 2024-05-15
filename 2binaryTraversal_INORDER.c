#include <stdio.h>
#include <stdlib.h>

// Define the structure of a binary tree node
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

// Function to insert a node into the binary tree
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

// Function to perform inorder traversal non-recursively
void inorderTraversal(struct TreeNode *root) {
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

// Function to count nodes on the longest path
int countNodesLongestPath(struct TreeNode *root) {
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

// Function to display the tree level-wise
void displayLevelWise(struct TreeNode *root) {
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

// Function to calculate the height of the tree
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

int main() {
    // Input from the user to create the binary tree
    int data, numNodes;
    struct TreeNode *root = NULL;

    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    printf("Enter the values of the nodes: ");
    for (int i = 0; i < numNodes; ++i) {
        scanf("%d", &data);
        insertNode(&root, data);
    }

    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("Count of nodes on the longest path: %d\n", countNodesLongestPath(root));

    printf("Displaying tree level-wise:\n");
    displayLevelWise(root);

    printf("Height of the tree: %d\n", height(root));

    return 0;
}
 