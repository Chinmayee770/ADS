#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Queue structure for BFS
struct Queue {
    int items[MAX];
    int front;
    int rear;
};

// Function to create a new queue
struct Queue *createQueue() {
    struct Queue *queue = (struct Queue *)malloc(sizeof(struct Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

// Function to check if the queue is empty
int isEmpty(struct Queue *queue) {
    if (queue->rear == -1)
        return 1;
    else
        return 0;
}

// Function to add an item to the queue
void enqueue(struct Queue *queue, int value) {
    if (queue->rear == MAX - 1)
        printf("Queue is full\n");
    else {
        if (queue->front == -1)
            queue->front = 0;
        queue->rear++;
        queue->items[queue->rear] = value;
    }
}

// Function to remove an item from the queue
int dequeue(struct Queue *queue) {
    int item;
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        item = -1;
    } else {
        item = queue->items[queue->front];
        queue->front++;
        if (queue->front > queue->rear) {
            queue->front = queue->rear = -1;
        }
    }
    return item;
}

// Graph structure
struct Graph {
    int vertices;
    int **adjMatrix;
};

// Function to create a new graph with adjacency matrix representation
struct Graph *createGraph(int vertices) {
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->vertices = vertices;

    graph->adjMatrix = (int **)malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; i++) {
        graph->adjMatrix[i] = (int *)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++)
            graph->adjMatrix[i][j] = 0;
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph *graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1;
}

// Function to perform Breadth-First Search (BFS) traversal
void BFS(struct Graph *graph, int startVertex) {
    struct Queue *queue = createQueue();
    int visited[MAX] = {0};

    visited[startVertex] = 1;
    enqueue(queue, startVertex);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        for (int i = 0; i < graph->vertices; i++) {
            if (graph->adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                enqueue(queue, i);
            }
        }
    }
    printf("\n");
}

// Function to perform Depth-First Search (DFS) traversal
void DFS(struct Graph *graph, int startVertex, int visited[]) {
    printf("%d ", startVertex);
    visited[startVertex] = 1;

    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adjMatrix[startVertex][i] == 1 && !visited[i]) {
            DFS(graph, i, visited);
        }
    }
}

// Main function
int main() {
    int vertices, edges, src, dest;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    struct Graph *graph = createGraph(vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        printf("Enter edge (source destination): ");
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }

    printf("\nBFS Traversal: ");
    BFS(graph, 0);

    printf("\nDFS Traversal: ");
    int visited[MAX] = {0};
    DFS(graph, 0, visited);
    printf("\n");

    return 0;
}
