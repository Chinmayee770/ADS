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

// Function to merge two sorted doubly linked lists
Node* mergeSortedLists(Node* list1, Node* list2) {
    if (list1 == NULL) {
        return list2;
    }
    if (list2 == NULL) {
        return list1;
    }
    Node* mergedList = NULL;
    Node* tail = NULL;
    while (list1 != NULL && list2 != NULL) {
        if (list1->data < list2->data) {
            if (mergedList == NULL) {
                mergedList = list1;
            } else {
                tail->next = list1;
                list1->prev = tail;
            }
            tail = list1;
            list1 = list1->next;
        } else {
            if (mergedList == NULL) {
                mergedList = list2;
            } else {
                tail->next = list2;
                list2->prev = tail;
            }
            tail = list2;
            list2 = list2->next;
        }
    }
    if (list1 != NULL) {
        tail->next = list1;
        list1->prev = tail;
    } else {
        tail->next = list2;
        if (list2 != NULL) {
            list2->prev = tail;
        }
    }
    return mergedList;
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

int main() {
    Node* list1 = NULL;
    Node* list2 = NULL;
    int n1, n2, data;

    printf("Enter the number of elements in the first list: ");
    scanf("%d", &n1);
    printf("Enter the elements in sorted order:\n");
    for (int i = 0; i < n1; i++) {
        scanf("%d", &data);
        list1 = insertAtEnd(list1, data);
    }

    printf("Enter the number of elements in the second list: ");
    scanf("%d", &n2);
    printf("Enter the elements in sorted order:\n");
    for (int i = 0; i < n2; i++) {
        scanf("%d", &data);
        list2 = insertAtEnd(list2, data);
    }

    printf("First list: ");
    displayForward(list1);
    printf("Second list: ");
    displayForward(list2);

    Node* mergedList = mergeSortedLists(list1, list2);
    printf("Merged list: ");
    displayForward(mergedList);

    // Freeing memory
    Node* temp;
    while (mergedList != NULL) {
        temp = mergedList;
        mergedList = mergedList->next;
        free(temp);
    }

    return 0;
}
