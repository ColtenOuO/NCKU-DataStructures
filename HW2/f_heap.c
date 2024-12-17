#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int root;
    int degree;
    int key;
    int* parent;
    int* left_child;
    int* right_child;
};
struct F_Heap {
    struct Node* root;
};
struct Root_LinkedList {
    struct F_Heap* next;
    struct F_Heap* head;
    struct F_Heap* min_ptr;
};
void F_Heap_Insert(struct Root_LinkedList* list, int key) {
    struct Root_LinkedList* new_list_node = (struct RootLinkedList*)calloc(1, sizeof(struct Root_LinkedList));
    if( list -> head == NULL ) {
        list -> head = new_list_node;
    }
    else {
        struct Root_LinkedList* now = list -> head;
        while( now -> next != NULL ) 
    }
}
struct OperatorType {
    int insert;
    int delete;
    int decrease;
    int extract_min;
    int exit;
};
struct InputData {
    struct OperatorType operator;
    int key, value;
};
void InputOperating(struct InputData* input_data) {
    char opt[20] = {};
    scanf("%s", opt);
    if( strcmp(opt, "insert") == 0 ) {
        (input_data -> operator).insert = 1;
        scanf("%d", &(input_data -> key));
    }
    if( strcmp(opt, "delete") == 0 ) {
        (input_data -> operator).delete = 1;
        scanf("%d", &(input_data -> key));
    }
    if( strcmp(opt, "decrease") == 0 ) {
        (input_data -> operator).decrease = 1;
        scanf("%d %d", &(input_data -> key), &(input_data -> value));
    }
    if( strcmp(opt, "extract-min") == 0 ) {
        (input_data -> operator).extract_min = 1;
    }
    if( strcmp(opt, "exit") == 0 ) {
        (input_data -> operator).exit = 1;
    }
}
int main() {
    while(1) {
        static struct InputData input_data;
        InputOperating(&input_data);
        if( input_data.operator.exit == 1 ) break;
        if( input_data.operator.insert == 1 ) {

        }
    }
}