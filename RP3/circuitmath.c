// Zavi Q

#include <stdio.h>

#define STACK_MAX_SIZE 100

int stack[STACK_MAX_SIZE];
int top;

void init() {
    top = -1;
}

void push(int item) {
    top++;
    stack[top] = item;
}

int pop() {
    int item = stack[top];
    top--;
    return item;
}

int main() {
    int n;
    scanf("%d", &n);

    int values[26];

    for (int i = 0; i < n; i++) {
        char val_char;
        scanf(" %c", &val_char);
        values[i] = (val_char == 'T');
    }

    init();

    char token;
    while (scanf(" %c", &token) == 1) {
        if (token >= 'A' && token <= 'Z') {
            push(values[token - 'A']);
        } else {
            int op1, op2;
            if (token == '*') {
                op2 = pop();
                op1 = pop();
                push(op1 && op2);
            } else if (token == '+') {
                op2 = pop();
                op1 = pop();
                push(op1 || op2);
            } else if (token == '-') {
                op1 = pop();
                push(!op1);
            }
        }
    }

    int final_result = pop();

    if (final_result) {
        printf("T\n");
    } else {
        printf("F\n");
    }

    return 0;
}