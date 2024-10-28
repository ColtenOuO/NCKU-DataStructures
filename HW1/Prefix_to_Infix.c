#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct StackNode {
    char *data;
    struct StackNode* prev;
};
void push(struct StackNode** top, char* insert_data) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode -> data = insert_data;
    newNode -> prev = *top;
    *top = newNode; 
}
char* top(struct StackNode** top) {
    return (*top) -> data;
}
void pop(struct StackNode** top) {
    struct StackNode* temp = (*top);
    *top = (*top) -> prev;
    free(temp);
    return;
}
int main() {
    struct StackNode* stack = NULL;
    char s[100] = {};
    scanf("%s",s);
    int sz = strlen(s);
    for(int i=sz-1;i>=0;i--) {
        if( s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' ) {
            char* top1 = top(&stack);
            pop(&stack);
            char* top2 = top(&stack);
            pop(&stack);
            char* unite = (char*)malloc(strlen(top1) + strlen(top2) + 2);
            sprintf(unite, "%s%c%s", top1, s[i], top2);
            push(&stack, unite);
        }
        else {
            char* c_str = (char*)malloc(2);
            c_str[0] = s[i];
            c_str[1] = '\0';
            push(&stack, c_str);
        }
    }

    char* ans = top(&stack);
    printf("%s\n",ans);

    return 0;
}