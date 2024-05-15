#include <stdio.h>
#include <stdlib.h>

// Structure for the stack
struct Stack {
    int top;
    int capacity;
    int* array;
};

// Function to create a new stack
struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (stack == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    if (stack->array == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return stack;
}

// Function to check if the stack is full
int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to push an element onto the stack
void push(struct Stack* stack, int data) {
    if (isFull(stack)) {
        printf("Stack Overflow\n");
        exit(EXIT_FAILURE);
    }
    stack->array[++stack->top] = data;
}

// Function to pop an element from the stack
int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->array[stack->top--];
}

// Function to calculate factorial using stack
int factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    struct Stack* stack = createStack(n);
    push(stack, 1);
    for (int i = 2; i <= n; i++) {
        push(stack, i * pop(stack));
    }
    int result = pop(stack);
    free(stack->array);
    free(stack);
    return result;
}

// Function to generate Fibonacci series using stack
void fibonacci(int n) {
    struct Stack* stack = createStack(n);
    push(stack, 0);
    push(stack, 1);
    printf("Fibonacci Series: ");
    printf("0 1 ");
    for (int i = 2; i < n; i++) {
        int a = pop(stack);
        int b = pop(stack);
        push(stack, a);
        push(stack, a + b);
        printf("%d ", a + b);
    }
    printf("\n");
    free(stack->array);
    free(stack);
}

// Main function
int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    // Calculate factorial
    printf("Factorial of %d is %d\n", number, factorial(number));

    // Generate Fibonacci series
    printf("Enter the number of terms for Fibonacci series: ");
    scanf("%d", &number);
    fibonacci(number);

    return 0;
}
