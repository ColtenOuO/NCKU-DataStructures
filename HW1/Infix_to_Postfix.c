#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct StackNode {
    char data;
    struct StackNode* prev;
};
void push(struct StackNode** top, char insert_data) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode -> data = insert_data;
    newNode -> prev = *top;
    *top = newNode; 
}
char top(struct StackNode** top) {
    return (*top) -> data;
}
void pop(struct StackNode** top) {
    struct StackNode* temp = (*top);
    *top = (*top) -> prev;
    free(temp);
    return;
}
int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}
int empty(struct StackNode** top) {
    return ( (*top) == NULL ? 1 : 0 );
}
int main() {
    struct StackNode* stack = NULL;
    char s[100] = {};
    scanf("%s",s);
    char postfix[200] = {};
    int sz = strlen(s), index = 0;
    for(int i=0;i<sz;i++) {
        if( s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '*' ) {
            while( empty(&stack) == 0 && precedence(top(&stack)) >= precedence(s[i]) ) {
                postfix[index++] = top(&stack);
                pop(&stack);
            }
            push(&stack, s[i]);
        }
        else {
            postfix[index++] = s[i];
        }
    }

    while( empty(&stack) == 0 ) postfix[index++] = top(&stack), pop(&stack);
    printf("%s\n", postfix);
    
    return 0;
}