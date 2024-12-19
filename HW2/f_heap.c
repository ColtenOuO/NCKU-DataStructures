#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int root;
    int degree;
    int height;
    int key;
    int tag;
    struct Node* parent;
    struct Child_LinkedList {
        struct Child_LinkedList* next;
        struct Node* data;
    };
    struct Child_LinkedList* child_head;
};

struct Node* key_reference[10001];

struct F_Heap_LinkedList {
    struct F_Heap_LinkedList* next;
    struct Node* data;
};
struct F_Heap_LinkedList* F_heap_head;

void Rebuild_LinkedList() {

}
void F_Heap_Merge_Check() {
    struct F_Heap_LinkedList* now_ptr = F_heap_head;
    struct Node** hash_mp;
    hash_mp = (struct Node**)calloc(10001, sizeof(struct Node*));
    while( now_ptr != NULL ) {
        if( hash_mp[now_ptr->data->degree] != NULL ) {

        }
        hash_mp[now_ptr->data->degree] = now_ptr -> data;

    }
}
void F_Heap_Insert(int key) {
    struct F_Heap_LinkedList* new_list_node = (struct F_Heap_LinkedList*)calloc(1, sizeof(struct F_Heap_LinkedList));
    if( F_heap_head == NULL ) {
        F_heap_head = new_list_node;
    }
    else {
        struct F_Heap_LinkedList* now = F_heap_head;
        while( now -> next != NULL ) now = now -> next;

        now -> next = new_list_node;
    }
    /* insert data */
    new_list_node -> data = (struct Node*)calloc(1, sizeof(struct Node));
    new_list_node -> data -> root = 1; // this is a root node
    new_list_node -> data -> degree = 0;
    new_list_node -> data -> height = 1;
    new_list_node -> data -> key = key;
    new_list_node -> data -> tag = 0;
    new_list_node -> data -> parent = NULL;
    new_list_node -> data -> child_head = NULL;
    key_reference[key] = new_list_node -> data;

    return;
}
void Cascating_Cut(struct Node* target) {
    // Step1: Update parent's child list
    struct Node* parent_ptr = target -> parent;
    struct Child_LinkedList* now_ptr = parent_ptr -> child_head;
    struct Child_LinkedList* last_ptr = NULL;
    while( now_ptr -> data -> key != target -> key ) last_ptr = now_ptr, now_ptr = now_ptr -> next;

    if( last_ptr == NULL ) { // Case1: target is a child head
        if( now_ptr -> next == NULL ) parent_ptr -> child_head = NULL;
        else parent_ptr -> child_head = now_ptr -> next;
    }
    else last_ptr -> next = now_ptr -> next; // Case2: target is not a child head

    parent_ptr -> degree -= 1; // degree -= 1

    if( target -> parent -> tag == 1 ) Cascating_Cut( target -> parent );

    target -> tag = 0;
    F_Heap_Root_Append(target);

    return;
}
void F_Heap_Root_Append(struct Node* target) {
    target -> root = 1;
    target -> parent = NULL;
    struct F_Heap_LinkedList* now = F_heap_head;
    while( now != NULL ) now = now -> next;
    struct F_Heap_LinkedList* new_node = (struct F_Heap_LinkedList*)calloc(1, sizeof(struct F_Heap_LinkedList));
    new_node -> data = target;
    new_node -> next = NULL;
    return;
}
void F_Heap_Delete(int key) {
    // get key (target) reference
    struct Node* target = key_reference[key];
    
    // Step1: delete from parent's child list
    if( target -> parent != NULL ) {
        struct Child_LinkedList* now = target -> parent -> child_head;
        struct Child_LinkedList* last = NULL; // record the last node
        while( now -> data -> key != key ) last = now, now = now -> next;
        if( last != NULL ) last -> next = now -> next; // delete node is not a child head
        else { // delete node is a child head
            if( now -> next == NULL ) now -> data -> child_head = NULL; // Case 1: no new child head
            else now -> data -> child_head = now -> next; // Case 2: new child head is next position
        }

        target -> parent -> degree -= 1;
        // Update the parent's tag
        if( target -> parent -> tag == 0 ) target -> parent -> tag = 1; // no tag before
        else {
            // TODO: cascating cut
            Cascating_Cut( target -> parent );
        }
    }
    
    // insert target's child to F_Heap Linked List
    struct Child_LinkedList* child_ptr = target -> child_head;
    while( child_ptr != NULL ) {
        F_Heap_Root_Append( child_ptr -> data );
        child_ptr = child_ptr -> next;
    }

    return;
}
void testing() {
    struct F_Heap_LinkedList* now = F_heap_head;
    while( now != NULL ) {
        printf("%d\n", now->data->key);
        now = now -> next;
    }
    return;
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
        F_Heap_Insert( input_data -> key );
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

    return;
}
int main() {
    while(1) {
        static struct InputData input_data;
        InputOperating(&input_data);
        if( input_data.operator.exit == 1 ) break;
    }

    //testing();
}