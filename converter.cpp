#include "converter.h"
#include "minfibheap.h"
#include "maxfibheap.h"

// Converts a MaxFibHeap to a new MinFibHeap by extracting all elements and inserting them.
// Note: This operation empties the source heap.
MinFibHeap* maxToMinHeap(MaxFibHeap* heap) {
    MinFibHeap* newHeap = new MinFibHeap();
    if (!heap) return newHeap;
    
    while (heap->getNodeCount() > 0) {
        Node *temp = heap->extractMax();
        if (temp) {
            newHeap->insert(temp->key);
            delete temp;
        }
    }
    return newHeap;
}

// Converts a MinFibHeap to a new MaxFibHeap by extracting all elements and inserting them.
// Note: This operation empties the source heap.
MaxFibHeap* minToMaxHeap(MinFibHeap* heap) {
    MaxFibHeap* newHeap = new MaxFibHeap();
    if (!heap) return newHeap;
    
    while (heap->getNodeCount() > 0) {
        Node *temp = heap->extractMin();
        if (temp) {
            newHeap->insert(temp->key);
            delete temp;
        }
    }
    return newHeap;
}