#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Stack implementation
#define MAX_SIZE 100

struct Stack {
    int top;
    char items[MAX_SIZE];
};

void push(struct Stack *s, char value) {
    if (s->top == MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        exit(EXIT_FAILURE);
    }
    s->items[++(s->top)] = value;
}

char pop(struct Stack *s) {
    if (s->top == -1) {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
    return s->items[(s->top)--];
}

char peek(struct Stack *s) {
    if (s->top == -1) {
        printf("Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return s->items[s->top];
}

int isEmpty(struct Stack *s) {
    return s->top == -1;
}

// Function to check if a character is an operator
int is_operator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

// Function to compare precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// Function to convert infix expression to postfix expression
char* infix_to_postfix(char* infix) {
    struct Stack stack;
    stack.top = -1;
    char* postfix = (char*)malloc(strlen(infix) * sizeof(char));
    int i = 0, j = 0;
    while (infix[i] != '\0') {
        if (isalnum(infix[i])) {
            postfix[j++] = infix[i++];
        } else if (infix[i] == '(') {
            push(&stack, infix[i++]);
        } else if (infix[i] == ')') {
            while (!isEmpty(&stack) && peek(&stack) != '(') {
                postfix[j++] = pop(&stack);
            }
            if (!isEmpty(&stack) && peek(&stack) != '(') {
                printf("Invalid Expression\n");
                exit(EXIT_FAILURE);
            } else {
                pop(&stack);
            }
            i++;
        } else if (is_operator(infix[i])) {
            while (!isEmpty(&stack) && precedence(infix[i]) <= precedence(peek(&stack))) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, infix[i++]);
        } else {
            printf("Invalid Character\n");
            exit(EXIT_FAILURE);
        }
    }
    while (!isEmpty(&stack)) {
        postfix[j++] = pop(&stack);
    }
    postfix[j] = '\0';
    return postfix;
}

// Function to evaluate postfix expression
int evaluate_postfix(char* postfix) {
    struct Stack stack;
    stack.top = -1;
    int i = 0;
    while (postfix[i] != '\0') {
        if (isdigit(postfix[i])) {
            push(&stack, postfix[i] - '0');
        } else if (is_operator(postfix[i])) {
            int operand2 = pop(&stack);
            int operand1 = pop(&stack);
            switch (postfix[i]) {
                case '+':
                    push(&stack, operand1 + operand2);
                    break;
                case '-':
                    push(&stack, operand1 - operand2);
                    break;
                case '*':
                    push(&stack, operand1 * operand2);
                    break;
                case '/':
                    push(&stack, operand1 / operand2);
                    break;
            }
        }
        i++;
    }
    return pop(&stack);
}

// Main function
int main() {
    char infix[100];
    printf("Enter infix expression: ");
    fgets(infix, sizeof(infix), stdin);
    infix[strcspn(infix, "\n")] = '\0'; // remove trailing newline character
    char* postfix = infix_to_postfix(infix);
    printf("Postfix expression: %s\n", postfix);
    int result = evaluate_postfix(postfix);
    printf("Result: %d\n", result);
    free(postfix); // free memory allocated for postfix expression
    return 0;
}
