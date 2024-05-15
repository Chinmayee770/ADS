#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in adjacency list
struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

// Structure to represent an adjacency list
struct AdjList {
    struct AdjListNode *head;
};

// Structure to represent a graph
struct Graph {
    int V;
    struct AdjList* array;
};

// Function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
    
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    
    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Since graph is undirected, add an edge from dest to src also
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Function to perform Breadth First Search traversal
void BFS(struct Graph* graph, int start) {
    // Array to keep track of visited vertices
    int* visited = (int*)malloc(graph->V * sizeof(int));
    int i;
    for (i = 0; i < graph->V; ++i)
        visited[i] = 0;

    // Queue for BFS
    int queue[graph->V];
    int front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);

        struct AdjListNode* temp = graph->array[current].head;
        while (temp) {
            int adj = temp->dest;
            if (!visited[adj]) {
                visited[adj] = 1;
                queue[rear++] = adj;
            }
            temp = temp->next;
        }
    }

    free(visited);
}

// Recursive function for Depth First Search traversal
void DFSUtil(struct Graph* graph, int v, int* visited) {
    visited[v] = 1;
    printf("%d ", v);

    struct AdjListNode* temp = graph->array[v].head;
    while (temp) {
        int adj = temp->dest;
        if (!visited[adj])
            DFSUtil(graph, adj, visited);
        temp = temp->next;
    }
}

// Function to perform Depth First Search traversal
void DFS(struct Graph* graph, int start) {
    int* visited = (int*)malloc(graph->V * sizeof(int));
    int i;
    for (i = 0; i < graph->V; ++i)
        visited[i] = 0;

    DFSUtil(graph, start, visited);

    free(visited);
}

// Main function
int main() {
    int V, E, src, dest, start;
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &V);
    printf("Enter the number of edges in the graph: ");
    scanf("%d", &E);

    struct Graph* graph = createGraph(V);

    printf("Enter the edges (source destination):\n");
    for (int i = 0; i < E; ++i) {
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    printf("Enter the starting vertex for traversal: ");
    scanf("%d", &start);

    printf("BFS Traversal: ");
    BFS(graph, start);
    printf("\n");

    printf("DFS Traversal: ");
    DFS(graph, start);
    printf("\n");

    return 0;
}
