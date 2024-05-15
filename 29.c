#include <stdio.h>
#include <stdlib.h>

// Structure for a single node in a doubly linked list
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

typedef struct Node Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning of the list
Node* insertAtBeginning(Node* head, int data) {
    Node* newNode = createNode(data);
    if (head == NULL) {
        return newNode;
    }
    newNode->next = head;
    head->prev = newNode;
    return newNode;
}

// Function to insert a node at the end of the list
Node* insertAtEnd(Node* head, int data) {
    Node* newNode = createNode(data);
    if (head == NULL) {
        return newNode;
    }
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;
    return head;
}

// Function to insert a node after a given node
Node* insertAfter(Node* head, Node* prevNode, int data) {
    if (prevNode == NULL) {
        printf("Previous node cannot be NULL\n");
        return head;
    }
    Node* newNode = createNode(data);
    newNode->next = prevNode->next;
    if (prevNode->next != NULL) {
        prevNode->next->prev = newNode;
    }
    prevNode->next = newNode;
    newNode->prev = prevNode;
    return head;
}

// Function to delete a node by value
Node* deleteNode(Node* head, int key) {
    if (head == NULL) {
        printf("List is empty\n");
        return NULL;
    }
    Node* temp = head;
    Node* prev = NULL;
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Key not found in the list\n");
        return head;
    }
    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }
    if (temp->next != NULL) {
        temp->next->prev = prev;
    }
    free(temp);
    return head;
}

// Function to display a doubly linked list forward
void displayForward(Node* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// Function to display a doubly linked list backward
void displayBackward(Node* tail) {
    if (tail == NULL) {
        printf("List is empty\n");
        return;
    }
    while (tail != NULL) {
        printf("%d -> ", tail->data);
        tail = tail->prev;
    }
    printf("NULL\n");
}

int main() {
    Node* head = NULL;
    int choice, data, key;

    do {
        printf("\nDoubly Linked List Operations\n");
        printf("1. Insert at beginning\n");
        printf("2. Insert at end\n");
        printf("3. Insert after a node\n");
        printf("4. Delete a node by value\n");
        printf("5. Display forward\n");
        printf("6. Display backward\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert at beginning: ");
                scanf("%d", &data);
                head = insertAtBeginning(head, data);
                break;
            case 2:
                printf("Enter data to insert at end: ");
                scanf("%d", &data);
                head = insertAtEnd(head, data);
                break;
            case 3:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                printf("Enter the value after which to insert: ");
                scanf("%d", &key);
                head = insertAfter(head, head, data);
                break;
            case 4:
                printf("Enter the value to delete: ");
                scanf("%d", &key);
                head = deleteNode(head, key);
                break;
            case 5:
                printf("Doubly linked list forward: ");
                displayForward(head);
                break;
            case 6:
                printf("Doubly linked list backward: ");
                displayBackward(head);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 7);

    // Freeing memory
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
