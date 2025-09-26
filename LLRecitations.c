#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char letter;
    struct node* next;
} node;

node* createNode(char letter) {
    node* newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL) {
        exit(1);
    }
    newNode->letter = letter;
    newNode->next = NULL;
    return newNode;
}

int length(node* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

char* toCString(node* head) {
    int len = length(head);
    char* str = (char*)malloc(sizeof(char) * (len + 1));
    if (str == NULL) {
        return NULL;
    }
    int i = 0;
    node* current = head;
    while (current != NULL) {
        str[i] = current->letter;
        i++;
        current = current->next;
    }
    str[i] = '\0';
    return str;
}

int main() {
    printf("--- Testing toCString function ---\n");

    node* head = createNode('T');
    head->next = createNode('E');
    head->next->next = createNode('S');
    head->next->next->next = createNode('T');

    printf("Original list created with characters: T, E, S, T\n");

    char* result_string = toCString(head);

    if (result_string != NULL) {
        printf("Function returned C string: \"%s\"\n", result_string);
        if (strcmp(result_string, "TEST") == 0) {
            printf("Verification PASSED.\n");
        } else {
            printf("Verification FAILED.\n");
        }
    } else {
        printf("Function returned NULL. Memory allocation might have failed.\n");
    }

    free(result_string);
    printf("Freed the dynamically allocated string.\n");

    node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("Freed all linked list nodes.\n");
    printf("----------------------------------\n");

    return 0;
}