#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

struct CircularQueue {
    int items[MAX_SIZE];
    int front, rear;
};

// Function to create a circular queue
struct CircularQueue* createQueue() {
    struct CircularQueue* queue = (struct CircularQueue*)malloc(sizeof(struct CircularQueue));
    if (queue == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

// Function to check if the queue is full
int isFull(struct CircularQueue* queue) {
    return (queue->front == 0 && queue->rear == MAX_SIZE - 1) || (queue->rear == (queue->front - 1) % (MAX_SIZE - 1));
}

// Function to check if the queue is empty
int isEmpty(struct CircularQueue* queue) {
    return queue->front == -1;
}

// Function to add an element to the rear of the queue
void enqueueRear(struct CircularQueue* queue, int value) {
    if (isFull(queue)) {
        printf("Queue is full\n");
        return;
    }

    if (queue->front == -1)
        queue->front = 0;
    queue->rear = (queue->rear + 1) % MAX_SIZE;
    queue->items[queue->rear] = value;
    printf("%d enqueued to rear\n", value);
}

// Function to add an element to the front of the queue
void enqueueFront(struct CircularQueue* queue, int value) {
    if (isFull(queue)) {
        printf("Queue is full\n");
        return;
    }

    if (queue->front == -1) {
        queue->front = 0;
        queue->rear = 0;
    } else if (queue->front == 0)
        queue->front = MAX_SIZE - 1;
    else
        queue->front = (queue->front - 1) % (MAX_SIZE - 1);
    queue->items[queue->front] = value;
    printf("%d enqueued to front\n", value);
}

// Function to remove an element from the front of the queue
int dequeueFront(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }

    int removedValue = queue->items[queue->front];
    if (queue->front == queue->rear)
        queue->front = queue->rear = -1;
    else
        queue->front = (queue->front + 1) % MAX_SIZE;
    printf("%d dequeued from front\n", removedValue);
    return removedValue;
}

// Function to remove an element from the rear of the queue
int dequeueRear(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }

    int removedValue = queue->items[queue->rear];
    if (queue->front == queue->rear)
        queue->front = queue->rear = -1;
    else if (queue->rear == 0)
        queue->rear = MAX_SIZE - 1;
    else
        queue->rear = queue->rear - 1;
    printf("%d dequeued from rear\n", removedValue);
    return removedValue;
}

// Function to display the queue
void display(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }

    int i;
    printf("Queue elements: ");
    if (queue->rear >= queue->front) {
        for (i = queue->front; i <= queue->rear; i++)
            printf("%d ", queue->items[i]);
    } else {
        for (i = queue->front; i < MAX_SIZE; i++)
            printf("%d ", queue->items[i]);
        for (i = 0; i <= queue->rear; i++)
            printf("%d ", queue->items[i]);
    }
    printf("\n");
}

int main() {
    struct CircularQueue* queue = createQueue();
    int choice, value;

    while (1) {
        printf("\nCircular Queue Operations:\n");
        printf("1. Enqueue Rear\n");
        printf("2. Enqueue Front\n");
        printf("3. Dequeue Rear\n");
        printf("4. Dequeue Front\n");
        printf("5. Display\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to enqueue to rear: ");
                scanf("%d", &value);
                enqueueRear(queue, value);
                break;
            case 2:
                printf("Enter the value to enqueue to front: ");
                scanf("%d", &value);
                enqueueFront(queue, value);
                break;
            case 3:
                dequeueRear(queue);
                break;
            case 4:
                dequeueFront(queue);
                break;
            case 5:
                display(queue);
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}
