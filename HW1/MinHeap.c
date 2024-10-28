#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 2000

struct MinHeap {
    int size;
    long long data[MAX_SIZE];
};
int parent_index(int idx) { return ( idx - 1 ) / 2; }
int leftChild_index(int idx) { return idx * 2 + 1; }
int rightChild_index(int idx) { return idx * 2 + 2; }
int getMin(struct MinHeap* heap) { return heap -> data[0]; }
void heapifyDown(struct MinHeap* heap, int original_pos) {
    int minIndex = original_pos;
    
    int left = leftChild_index(original_pos);
    if( left < heap -> size && heap -> data[left] < heap -> data[minIndex] ) minIndex = left;

    int right = rightChild_index(original_pos);
    if( right < heap -> size && heap -> data[right] < heap -> data[minIndex] ) minIndex = right;

    if( original_pos != minIndex ) {
        int temp = heap -> data[original_pos];
        heap -> data[original_pos] = heap -> data[minIndex];
        heap -> data[minIndex] = temp;

        heapifyDown(heap, minIndex);
    }
}
void deleteMin(struct MinHeap* heap) {
    heap -> data[0] = heap -> data[ ( heap -> size ) - 1];
    heap -> size = ( heap -> size ) - 1;
    heapifyDown(heap, 0);
}
void heapifyUp(struct MinHeap* heap, int original_pos ) {
    if( original_pos == 0 ) return;
    if( heap->data[parent_index(original_pos)] > heap->data[original_pos] ) {
        int temp = heap->data[original_pos];
        heap->data[original_pos] = heap->data[parent_index(original_pos)];
        heap->data[parent_index(original_pos)] = temp;

        heapifyUp(heap, parent_index(original_pos));
    }
}
void deleteValue(struct MinHeap* heap, long long value) {
    int pos = -1;
    for (int i = 0; i < heap->size; i++) {
        if (heap->data[i] == value) {
            pos = i;
            break;
        }
    }

    heap->data[pos] = heap->data[heap->size - 1];
    heap->size--;

    heapifyDown(heap, pos);
    heapifyUp(heap, pos);
}
void insert(struct MinHeap* heap, long long value) {
    heap -> data[heap -> size] = value;
    heap -> size = ( heap -> size ) + 1;
    heapifyUp(heap, heap->size - 1);
}
int main() {
    struct MinHeap min_heap;
    min_heap.size = 0;
    
    char option[30] = {};
    while( scanf("%s", option) != EOF ) {
        long long value;
        scanf("%lld", &value);
        if( option[0] == 'i' ) {
            insert(&min_heap, value);
        }
        else {
            deleteValue(&min_heap, value);
        }
    }

    for(int i=0;i<min_heap.size;i++) printf("%lld ", min_heap.data[i]);
    printf("\n");

    return 0;
}