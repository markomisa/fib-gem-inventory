#ifndef MAXFIBHEAP_H
#define MAXFIBHEAP_H

#include "node.h"
#include <iostream>

class MaxFibHeap {
public:
    MaxFibHeap() : rootList(nullptr), maxNode(nullptr), nodeCount(0) {}
    Node* maximum() { return maxNode; }
    void insert(int key);
    Node* extractMax();
    void printHeap();
    ~MaxFibHeap();
    int getNodeCount() const { return nodeCount; }
    static MaxFibHeap* heapUnion(MaxFibHeap* heap1, MaxFibHeap* heap2);
    
protected:
    void heapLink(Node* x, Node* y);
    void consolidate();
    void removeFromRootList(Node* node);
    void mergeWithRootList(Node* node);
    void mergeWithChildList(Node* parent, Node* node);

private:
    Node* rootList;
    Node* maxNode;
    int nodeCount;
};

#endif // MAXFIBHEAP_H