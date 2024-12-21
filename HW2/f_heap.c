#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Child_LinkedList {
    struct Child_LinkedList* next;
    struct Node* data;
};
struct Node {
    int root;
    int degree;
    int height;
    int key;
    int tag;
    struct Node* parent;
    struct Child_LinkedList* child_head;
};

struct Node* key_reference[10001];

struct F_Heap_LinkedList {
    struct F_Heap_LinkedList* next;
    struct Node* data;
};
struct F_Heap_LinkedList* F_heap_head;

int qsort_compare(const void* a, const void* b) {
    struct F_Heap_LinkedList* target1 = *(struct F_Heap_LinkedList**)a;
    struct F_Heap_LinkedList* target2 = *(struct F_Heap_LinkedList**)b;

    return (target1->data->key) - (target2->data->key);
}
int qsort_compare_degree(const void* a, const void* b) {
    struct F_Heap_LinkedList* target1 = *(struct F_Heap_LinkedList**)a;
    struct F_Heap_LinkedList* target2 = *(struct F_Heap_LinkedList**)b;
    return (target1->data->degree) - (target2->data->degree);
}
void Rebuild_LinkedList() {
    int linked_list_len = 0;
    static struct F_Heap_LinkedList* tmp_arr[10001];
    struct F_Heap_LinkedList* now_ptr = F_heap_head;
    while( now_ptr != NULL ) {
        tmp_arr[linked_list_len++] = now_ptr;
        now_ptr = now_ptr -> next;
    }

    qsort(tmp_arr, linked_list_len, sizeof(struct F_Heap_LinkedList*), qsort_compare);
    for (int i = 0;i<linked_list_len-1;i++) tmp_arr[i]->next = tmp_arr[i + 1];
    tmp_arr[linked_list_len - 1] -> next = NULL;
    F_heap_head = tmp_arr[0];
    return;
}
void Rebuild_LinkedList_by_Degree() {
    int linked_list_len = 0;
    static struct F_Heap_LinkedList* tmp_arr[10001];
    struct F_Heap_LinkedList* now_ptr = F_heap_head;
    while( now_ptr != NULL ) {
        tmp_arr[linked_list_len++] = now_ptr;
        now_ptr = now_ptr -> next;
    }

    qsort(tmp_arr, linked_list_len, sizeof(struct F_Heap_LinkedList*), qsort_compare_degree);
    for (int i = 0;i<linked_list_len-1;i++) tmp_arr[i]->next = tmp_arr[i + 1];
    tmp_arr[linked_list_len - 1] -> next = NULL;
    F_heap_head = tmp_arr[0];
    return;
}
void F_Heap_Root_Append(struct Node* target) {
    target -> root = 1;
    target -> parent = NULL;
    struct F_Heap_LinkedList* now = F_heap_head;
    
    while( now -> next != NULL ) now = now -> next;
    struct F_Heap_LinkedList* new_node = (struct F_Heap_LinkedList*)calloc(1, sizeof(struct F_Heap_LinkedList));
    new_node -> data = target;
    new_node -> next = NULL;
    
    if( F_heap_head == NULL ) {
        F_heap_head = new_node;
    }
    else {
        now -> next = new_node;
    }

    return;
}
void F_Heap_Merge(struct F_Heap_LinkedList* target1, struct F_Heap_LinkedList* target2) {
    // target1 merge to target2
    struct Node* target1_node = target1 -> data;
    struct Node* target2_node = target2 -> data;
    target1_node -> root = 0;
    target2_node -> degree += 1;
    // Step1: find the target2's last child pointer
    struct Child_LinkedList* now_ptr = target2_node -> child_head;
    while( now_ptr != NULL && now_ptr -> next != NULL ) now_ptr = now_ptr -> next;
    // Step2: append taregt1 to target2's child linked list
    struct Child_LinkedList* new_node = (struct Child_LinkedList*)calloc(1, sizeof(struct Child_LinkedList));
    new_node -> data = target1_node;
    new_node -> next = NULL;
    if( target2_node -> child_head == NULL ) {
        target2_node -> child_head = new_node;
    }
    else now_ptr -> next = new_node;

    // Step3: remove target1 from F-Heap's LinkedList
    struct F_Heap_LinkedList* now_ptr2 = F_heap_head;
    if( target1 == F_heap_head ) { // Case1: target1 is head of linked list
        F_heap_head = target1 -> next;
    }
    else { // Case2: target1 is not head of linked list
        struct F_Heap_LinkedList* last_ptr = NULL;
        while( now_ptr2 != target1 ) last_ptr = now_ptr2, now_ptr2 = now_ptr2 -> next;
        last_ptr -> next = now_ptr2 -> next;
    }

    target1_node -> parent = target2_node;
    return;
}
void F_Heap_Merge_Check() {
    Rebuild_LinkedList(); // sort by degree of root
    struct F_Heap_LinkedList* now_ptr = F_heap_head;
    struct F_Heap_LinkedList** hash_mp;
    hash_mp = (struct F_Heap_LinkedList**)calloc(10001, sizeof(struct F_Heap_LinkedList*));
    while( now_ptr != NULL ) {
        if( hash_mp[now_ptr->data->degree] != NULL ) {
            int save_degree = now_ptr -> data -> degree;
            F_Heap_Merge(now_ptr, hash_mp[now_ptr->data->degree]);
            free(hash_mp);
            hash_mp = (struct F_Heap_LinkedList**)calloc(10001, sizeof(struct F_Heap_LinkedList*));
            Rebuild_LinkedList();
            now_ptr = F_heap_head;
            continue;
        }
        else hash_mp[now_ptr->data->degree] = now_ptr;

        now_ptr = now_ptr -> next;
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
            if( now -> next == NULL )  target -> parent -> child_head = NULL; // Case 1: no new child head
            else target -> parent -> child_head = now -> next; // Case 2: new child head is next position
        }
        target -> parent -> degree -= 1;
        // Update the parent's tag
        if( target -> parent -> tag == 0 ) target -> parent -> tag = 1; // no tag before
        else if( target -> parent -> root != 1 ) {
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

    // target is root 
    if( target -> parent == NULL ) {
        struct F_Heap_LinkedList* now_ptr = F_heap_head;
        struct F_Heap_LinkedList* last_ptr = NULL;
        while( now_ptr -> data != target ) {
            last_ptr = now_ptr;
            now_ptr = now_ptr -> next;
        }
        if( last_ptr == NULL ) { // target is head of root linked list
            F_heap_head = now_ptr -> next;
        }
        else last_ptr -> next = now_ptr -> next;
    }

    return;
}
void F_Heap_Decrease(int key, int value) {
    struct Node* target = key_reference[key];
    target -> key -= value;
    key_reference[key] = NULL;
    key_reference[key-value] = target;
    if( target -> parent != NULL && target -> key < target -> parent -> key ) {
        // Step1: remove target from parent's child list
        struct Child_LinkedList* now_ptr = target -> parent -> child_head;
        // Case1: head
        if( now_ptr -> data == target ) {
            if( now_ptr -> next != NULL ) target -> parent -> child_head = now_ptr -> next;
            else target -> parent -> child_head = NULL;
        }
        else {
            struct Child_LinkedList* last_ptr = NULL;
            while( now_ptr -> data != target ) last_ptr = now_ptr, now_ptr = now_ptr -> next;
            last_ptr -> next = now_ptr -> next;
        }
        if( target -> parent -> tag == 1 ) {
            target -> parent -> degree -= 1;
            F_Heap_Root_Append(target);
            Cascating_Cut(target->parent);
        }
        else {
            target -> parent -> tag = 1;
            target -> parent -> degree -= 1;
            F_Heap_Root_Append(target);
        }
    }
}
struct Node* find_min() {
    struct F_Heap_LinkedList* now_ptr = F_heap_head;
    struct Node* target = NULL;
    int mn = 1e9;
    while( now_ptr != NULL ) {
        if( now_ptr -> data -> key < mn ) {
            mn = now_ptr -> data -> key;
            target = now_ptr -> data;
        }

        now_ptr = now_ptr -> next;
    }
    return target;
}
int qsort_compare_child_key(const void* a, const void* b) {
    struct Child_LinkedList* target1 = *(struct Child_LinkedList**)a;
    struct Child_LinkedList* target2 = *(struct Child_LinkedList**)b;
    return (target1->data->key) - (target2->data->key);
}
void bfs(struct Node* start) {
    struct Node* queue[10001];
    int idx = 1, now_idx = 0;
    queue[0] = start;
    while( now_idx != idx ) {
        printf("%d ", queue[now_idx] -> key);
        struct Child_LinkedList* now_ptr = queue[now_idx] -> child_head;
        int index = 0;
        struct Child_LinkedList* tmp[10001];
        while( now_ptr != NULL ) tmp[index++] = now_ptr, now_ptr = now_ptr -> next;
        qsort(tmp, index, sizeof(struct Child_LinkedList*), qsort_compare_child_key);
        for(int i=0;i<index;i++) queue[idx++] = tmp[i] -> data;
        now_idx++;
    }
    printf("\n");
}
void output() {
    Rebuild_LinkedList_by_Degree();
    struct F_Heap_LinkedList* now_ptr = F_heap_head;
    while( now_ptr != NULL ) {
        bfs(now_ptr->data);
        now_ptr = now_ptr -> next;
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
        F_Heap_Delete( input_data -> key );
        F_Heap_Merge_Check();
    }
    if( strcmp(opt, "decrease") == 0 ) {
        (input_data -> operator).decrease = 1;
        scanf("%d %d", &(input_data -> key), &(input_data -> value));
        F_Heap_Decrease( input_data -> key, input_data -> value );
    }
    if( strcmp(opt, "extract-min") == 0 ) {
        (input_data -> operator).extract_min = 1;
        F_Heap_Delete(find_min()->key);
        F_Heap_Merge_Check();
    }
    if( strcmp(opt, "exit") == 0 ) {
        (input_data -> operator).exit = 1;
    }

    return;
}
int main() {
    while(1) {
        struct InputData input_data;
        InputOperating(&input_data);
        if( input_data.operator.exit == 1 ) break;
    }

    output();
    //testing();
}