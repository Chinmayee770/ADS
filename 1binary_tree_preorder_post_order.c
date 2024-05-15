#include <stdio.h>
#include <stdlib.h>

// Structure for a node of binary tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Structure for stack used in traversal
struct Stack {
    int capacity;
    int top;
    struct Node** array;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to create a stack of given capacity
struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (stack == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (struct Node**)malloc(stack->capacity * sizeof(struct Node*));
    if (stack->array == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    return stack;
}

// Function to push a node to stack
void push(struct Stack* stack, struct Node* node) {
    if (stack->top == stack->capacity - 1) {
        printf("Stack overflow\n");
        exit(1);
    }
    stack->array[++stack->top] = node;
}

// Function to pop a node from stack
struct Node* pop(struct Stack* stack) {
    if (stack->top == -1) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack->array[stack->top--];
}

// Function to check if stack is empty
int isEmptyStack(struct Stack* stack) {
    return stack->top == -1;
}

// Function to perform preorder traversal iteratively
void preorderTraversal(struct Node* root) {
    if (root == NULL)
        return;

    struct Stack* stack = createStack(100); // Assuming maximum of 100 nodes in the tree
    push(stack, root);

    while (!isEmptyStack(stack)) {
        struct Node* current = pop(stack);
        printf("%d ", current->data);

        if (current->right != NULL)
            push(stack, current->right);
        if (current->left != NULL)
            push(stack, current->left);
    }
}

// Function to perform postorder traversal iteratively
void postorderTraversal(struct Node* root) {
    if (root == NULL)
        return;

    struct Stack* stack1 = createStack(100); // Assuming maximum of 100 nodes in the tree
    struct Stack* stack2 = createStack(100);

    push(stack1, root);
    while (!isEmptyStack(stack1)) {
        struct Node* current = pop(stack1);
        push(stack2, current);

        if (current->left != NULL)
            push(stack1, current->left);
        if (current->right != NULL)
            push(stack1, current->right);
    }

    while (!isEmptyStack(stack2)) {
        struct Node* temp = pop(stack2);
        printf("%d ", temp->data);
    }
}

// Function to count total number of nodes in the tree
int countNodes(struct Node* root) {
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Function to find the height of the tree
int height(struct Node* root) {
    if (root == NULL)
        return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

int main() {
    struct Node* root = NULL;
    int choice, data;
    
    do {
        printf("\n1. Insert a node\n");
        printf("2. Preorder Traversal\n");
        printf("3. Postorder Traversal\n");
        printf("4. Count total number of nodes\n");
        printf("5. Display height of the tree\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Enter data to be inserted: ");
                scanf("%d", &data);
                if (root == NULL)
                    root = createNode(data);
                else {
                    struct Node* temp = root;
                    struct Node* parent;
                    while (temp != NULL) {
                        parent = temp;
                        if (data <= temp->data)
                            temp = temp->left;
                        else
                            temp = temp->right;
                    }
                    if (data <= parent->data)
                        parent->left = createNode(data);
                    else
                        parent->right = createNode(data);
                }
                break;
            case 2:
                printf("Preorder Traversal: ");
                preorderTraversal(root);
                printf("\n");
                break;
            case 3:
                printf("Postorder Traversal: ");
                postorderTraversal(root);
                printf("\n");
                break;
            case 4:
                printf("Total number of nodes: %d\n", countNodes(root));
                break;
            case 5:
                printf("Height of the tree: %d\n", height(root));
                break;
            case 6:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 6);
    
    return 0;
}
