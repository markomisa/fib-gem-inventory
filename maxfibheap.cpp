#include "maxfibheap.h"
#include <vector>
#include <queue>
#include <set>

// Helper functions (protected)
void MaxFibHeap::removeFromRootList(Node *node)
{
    if (nodeCount == 1) {
        rootList = nullptr;
        return;
    }
    if (node == rootList) {
        rootList = node->right;
    }
    node->left->right = node->right;
    node->right->left = node->left;
}

void MaxFibHeap::mergeWithRootList(Node *node)
{
    if (rootList == nullptr) {
        rootList = node;
        node->left = node;
        node->right = node;
    } else {
        node->right = rootList;
        node->left = rootList->left;
        rootList->left->right = node;
        rootList->left = node;
    }
}

void MaxFibHeap::mergeWithChildList(Node *parent, Node *node) {
    if (!parent->child) {
        parent->child = node;
        node->left = node;
        node->right = node;
    }
    else {
        // Remove 'node' from its current list (if any) and insert it after parent->child
        node->right = parent->child->right;
        node->left = parent->child;
        parent->child->right->left = node;
        parent->child->right = node;
    }
}

void MaxFibHeap::heapLink(Node *y, Node *x)
{
    removeFromRootList(y);
    y->left = y->right = y; 
    mergeWithChildList(x, y );
    x->degree++;
    y->parent = x;
}

void MaxFibHeap::consolidate()
{
    std::vector<Node*> v(nodeCount + 1, nullptr);
    std::vector<Node*> nodes;
    if (!rootList) return; 

    Node *curr = rootList;
    do {
        nodes.push_back(curr);
        curr = curr->right;
    } while (curr != rootList);

    for(Node *x : nodes){
        if (x->parent != nullptr) continue; // Skip nodes that were already linked
        
        int degree = x->degree;
        while(degree < v.size() && v[degree] != nullptr){
            Node *y = v[degree];
            if(x->key < y->key){ // Max Heap: larger key becomes parent
                Node* temp = x;
                x = y;
                y = temp;
            }
            heapLink(y, x);
            v[degree] = nullptr;
            degree++;
        }
        if(degree < v.size()) {
            v[degree] = x;
        }
    }
    
    rootList = nullptr;
    maxNode = nullptr;

    for(Node *node : v){
        if(node != nullptr){
            node->parent = nullptr; 
            if (rootList == nullptr) {
                rootList = node;
                node->left = node;
                node->right = node;
            } else {
                // Re-merge to root list
                Node* first = rootList;
                Node* last = rootList->left;
                
                node->right = first;
                node->left = last;
                last->right = node;
                first->left = node;
            }

            if(maxNode == nullptr || node->key > maxNode->key){
                maxNode = node;
            }
        }
    }
    if (maxNode) {
        rootList = maxNode; // Reset rootList pointer to maxNode for consistency
    }
}

// Public methods
void MaxFibHeap::insert(int key)
{
    Node* newNode = new Node(key);
    mergeWithRootList(newNode);

    if(maxNode == nullptr || key > maxNode->key) maxNode = newNode;
    nodeCount++;
}

Node *MaxFibHeap::extractMax()
{
    if (nodeCount == 0) return nullptr;
    
    Node *curr = maxNode;
    if(curr){
        if (curr->child) {
            Node* first = curr->child;
            Node* temp = first;
            
            // Collect children to move to root list
            std::vector<Node*> children;
            Node* child = first;
            do {
                children.push_back(child);
                child = child->right;
            } while (child != temp);
            
            curr->child = nullptr;

            // Move children to root list
            for (Node* childNode : children) {
                childNode->parent = nullptr;
                mergeWithRootList(childNode);
            }
        }
        
        removeFromRootList(curr);

        if (curr == curr->right || nodeCount == 1){
            maxNode = nullptr;
            rootList = nullptr;
        }
        else {
            maxNode = curr->right; 
            consolidate();
        }
        nodeCount--;
    }
    return curr;
}

void MaxFibHeap::printHeap()
{
    if (!maxNode) {
        std::cout << "Prazan!" << std::endl;
        return;
    }

    std::queue<Node*> nodeQueue;
    std::set<Node*> visited;

    Node* current = maxNode;
    do {
        nodeQueue.push(current);
        visited.insert(current);
        current = current->right;
    } while (current != maxNode);

    while (!nodeQueue.empty()) {
        size_t levelSize = nodeQueue.size();
        std::cout << "| ";

        for (size_t i = 0; i < levelSize; ++i) {
            Node* node = nodeQueue.front();
            nodeQueue.pop();

            std::cout << node->key << "(" << node->degree << ") ";

            if (node->child) {
                Node* child = node->child;
                do {
                    if (visited.find(child) == visited.end()) {
                        nodeQueue.push(child);
                        visited.insert(child);
                    }
                    child = child->right;
                } while (child != node->child);
            }
        }
        std::cout << "|" << std::endl;
    }
}

MaxFibHeap::~MaxFibHeap() 
{
    if (!maxNode) {
        return;
    }
    
    std::queue<Node*> nodeQueue;
    std::set<Node*> visited;

    Node* current = maxNode;
    do {
        nodeQueue.push(current);
        visited.insert(current);
        current = current->right;
    } while (current != maxNode);

    while (!nodeQueue.empty()) {
        Node* node = nodeQueue.front();
        nodeQueue.pop();

        if (node->child) {
            Node* child = node->child;
            do {
                if (visited.find(child) == visited.end()) {
                    nodeQueue.push(child);
                    visited.insert(child);
                }
                child = child->right;
            } while (child != node->child);
        }

        delete node;
    }
}

MaxFibHeap *MaxFibHeap::heapUnion(MaxFibHeap *heap1, MaxFibHeap *heap2) {
    if (!heap1 || heap1->nodeCount == 0) { 
        if (heap2) { heap2->rootList = nullptr; heap2->maxNode = nullptr; heap2->nodeCount = 0; }
        return heap2; 
    }
    if (!heap2 || heap2->nodeCount == 0) { 
        if (heap1) { heap1->rootList = nullptr; heap1->maxNode = nullptr; heap1->nodeCount = 0; }
        return heap1; 
    }
    
    MaxFibHeap *newHeap = new MaxFibHeap();
    newHeap->nodeCount = heap1->nodeCount + heap2->nodeCount;
    newHeap->rootList = heap1->rootList;
    
    newHeap->maxNode = (heap1->maxNode->key > heap2->maxNode->key) ? heap1->maxNode : heap2->maxNode;

    // Merge the root lists
    Node *h1_last = heap1->rootList->left;
    Node *h2_first = heap2->rootList;
    Node *h2_last = heap2->rootList->left;

    h1_last->right = h2_first;
    h2_first->left = h1_last;

    h2_last->right = newHeap->rootList;
    newHeap->rootList->left = h2_last;
    
    // Clear old heap references
    heap1->rootList = nullptr;
    heap1->maxNode = nullptr;
    heap1->nodeCount = 0;
    heap2->rootList = nullptr;
    heap2->maxNode = nullptr;
    heap2->nodeCount = 0;

    return newHeap;
}