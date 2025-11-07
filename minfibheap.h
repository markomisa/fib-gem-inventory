#ifndef MINFIBHEAP_H
#define MINFIBHEAP_H

#include "node.h"
#include <iostream>

class MinFibHeap {
public:
    MinFibHeap() : rootList(nullptr), minNode(nullptr), nodeCount(0) {}
    Node* minimum() { return minNode; }
    void insert(int key);
    Node* extractMin();
    void printHeap();
    void kSmallestElements(int k);
    ~MinFibHeap();
    int getNodeCount() const { return nodeCount; }
    static MinFibHeap* heapUnion(MinFibHeap* heap1, MinFibHeap* heap2);

protected:
    void heapLink(Node* x, Node* y);
    void consolidate();
    void removeFromRootList(Node* node);
    void mergeWithRootList(Node* node);
    void mergeWithChildList(Node* parent, Node* node);

private:
    Node* rootList;
    Node* minNode;
    int nodeCount;
};

#endif // MINFIBHEAP_H