#ifndef STACK_H
#define STACK_H

#define MAX_STACK_SIZE 1000

typedef struct {
    int data[2];
} StackElement;

typedef struct {
    StackElement elements[MAX_STACK_SIZE];
    int top;
} Stack;

// Initialize the stack
void initialize(Stack *stack) {
    stack->top = -1;
}

// Check if the stack is empty
int isEmpty(Stack *stack) {
    return stack->top == -1;
}

// Check if the stack is full
int isFull(Stack *stack) {
    return stack->top == MAX_STACK_SIZE - 1;
}

// Push an element onto the stack
void push(Stack *stack, int value1, int value2) {
    stack->top++;
    stack->elements[stack->top].data[0] = value1;
    stack->elements[stack->top].data[1] = value2;
}

// Pop an element from the stack
StackElement pop(Stack *stack) {
    StackElement poppedElement = stack->elements[stack->top];
    stack->top--;
    return poppedElement;
}

#endif // STACK_H