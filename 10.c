#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int data) {
    if (root == NULL)
        return createNode(data);
    
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

void mirrorImage(struct Node* root) {
    if (root == NULL)
        return;
    else {
        struct Node* temp;
        
        // Swap left and right subtrees
        mirrorImage(root->left);
        mirrorImage(root->right);
        
        temp = root->left;
        root->left = root->right;
        root->right = temp;
    }
}

int treeHeight(struct Node* root) {
    if (root == NULL)
        return -1;

    int height = 0;
    struct Node* stack[100]; // Assuming a maximum of 100 nodes
    int top = -1;
    struct Node* current = root;

    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }

        current = stack[top--];

        if (current->right == NULL && top + 1 > height)
            height = top + 1;

        current = current->right;
    }

    return height;
}

void displayInorder(struct Node* root) {
    if (root == NULL)
        return;

    displayInorder(root->left);
    printf("%d ", root->data);
    displayInorder(root->right);
}

int main() {
    struct Node* root = NULL;
    int choice, data;

    do {
        printf("\n1. Insert element into the tree\n");
        printf("2. Display Inorder Traversal\n");
        printf("3. Display Mirror Image\n");
        printf("4. Display Height of Tree\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;
            case 2:
                printf("Inorder Traversal: ");
                displayInorder(root);
                printf("\n");
                break;
            case 3:
                printf("Mirror Image of the tree: ");
                mirrorImage(root);
                displayInorder(root);
                mirrorImage(root); // Restore original tree
                printf("\n");
                break;
            case 4:
                printf("Height of the tree: %d\n", treeHeight(root));
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 5);

    return 0;
}
