#include <stdio.h>
#include <stdlib.h>

// Define the structure of an employee record
struct Employee {
    int emp_id;
    char name[50];
    char department[50];
};

// Define the structure of a binary search tree node
struct TreeNode {
    struct Employee emp;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function to create a new node
struct TreeNode *createNode(struct Employee emp) {
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->emp = emp;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert an employee record into the binary search tree
struct TreeNode *insertNode(struct TreeNode *root, struct Employee emp) {
    if (root == NULL)
        return createNode(emp);

    if (emp.emp_id < root->emp.emp_id)
        root->left = insertNode(root->left, emp);
    else if (emp.emp_id > root->emp.emp_id)
        root->right = insertNode(root->right, emp);

    return root;
}

// Function to search for an employee record by employee ID in the binary search tree
struct TreeNode *searchEmployee(struct TreeNode *root, int emp_id) {
    while (root != NULL) {
        if (emp_id < root->emp.emp_id)
            root = root->left;
        else if (emp_id > root->emp.emp_id)
            root = root->right;
        else
            return root;
    }
    return NULL; // Employee not found
}

// Function to perform inorder traversal of the binary search tree
void inorderTraversal(struct TreeNode *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Employee ID: %d, Name: %s, Department: %s\n", root->emp.emp_id, root->emp.name, root->emp.department);
        inorderTraversal(root->right);
    }
}

int main() {
    struct TreeNode *root = NULL;
    struct Employee emp;
    int choice, search_id;

    do {
        printf("\nEmployee Record Management System:");
        printf("\n1. Add Employee Record");
        printf("\n2. Search Employee Record");
        printf("\n3. Display Employee Records (Sorted by Employee ID)");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Employee ID: ");
                scanf("%d", &emp.emp_id);
                printf("Enter Name: ");
                scanf("%s", emp.name);
                printf("Enter Department: ");
                scanf("%s", emp.department);
                root = insertNode(root, emp);
                break;
            case 2:
                printf("Enter Employee ID to search: ");
                scanf("%d", &search_id);
                if (searchEmployee(root, search_id) != NULL)
                    printf("Employee Record found:\nEmployee ID: %d, Name: %s, Department: %s\n", root->emp.emp_id, root->emp.name, root->emp.department);
                else
                    printf("Employee Record not found.\n");
                break;
            case 3:
                printf("Employee Records (Sorted by Employee ID):\n");
                inorderTraversal(root);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}
