#include "minfibheap.h"
#include <vector>
#include <queue>
#include <set>

// Helper functions (protected)
void MinFibHeap::removeFromRootList(Node *node)
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

void MinFibHeap::mergeWithRootList(Node *node)
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

void MinFibHeap::mergeWithChildList(Node *parent, Node *node) {
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

void MinFibHeap::heapLink(Node *y, Node *x)
{
    removeFromRootList(y);
    y->left = y->right = y; 
    mergeWithChildList(x, y );
    x->degree++;
    y->parent = x;
}

void MinFibHeap::consolidate()
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
            if(x->key > y->key){ // Min Heap: smaller key becomes parent
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
    minNode = nullptr;

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
            
            if(minNode == nullptr || node->key < minNode->key){
                minNode = node;
            }
        }
    }
    if (minNode) {
        rootList = minNode; // Reset rootList pointer to minNode for consistency
    }
}

// Public methods
void MinFibHeap::insert(int key)
{
    Node* newNode = new Node(key);
    mergeWithRootList(newNode);

    if(minNode == nullptr || key < minNode->key) minNode = newNode;
    nodeCount++;
}

Node *MinFibHeap::extractMin()
{
    if (nodeCount == 0) return nullptr;

    Node *curr = minNode;
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
            minNode = nullptr;
            rootList = nullptr;
        }
        else {
            minNode = curr->right; 
            consolidate();
        }
        nodeCount--;
    }
    return curr;
}

void MinFibHeap::printHeap()
{
    if (!minNode) {
        std::cout << "Prazan!" << std::endl;
        return;
    }

    std::queue<Node*> nodeQueue;
    std::set<Node*> visited;

    Node* current = minNode;
    do {
        nodeQueue.push(current);
        visited.insert(current);
        current = current->right;
    } while (current != minNode);

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

void MinFibHeap::kSmallestElements(int k) {
    std::cout << "Najmanji " << k << " elementi: ";
    bool first = true;
    for (int i = 0; i < k && nodeCount > 0; i++) {
        Node *min = extractMin();
        if (!first) std::cout << ", ";
        std::cout << min->key;
        first = false;
        delete min;
    }
    std::cout << std::endl;
}

MinFibHeap::~MinFibHeap()
{
    if (!minNode) {
        return;
    }
    
    std::queue<Node*> nodeQueue;
    std::set<Node*> visited;

    Node* current = minNode;
    do {
        nodeQueue.push(current);
        visited.insert(current);
        current = current->right;
    } while (current != minNode);

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

MinFibHeap *MinFibHeap::heapUnion(MinFibHeap *heap1, MinFibHeap *heap2) {
    if (!heap1 || heap1->nodeCount == 0) { 
        if (heap2) { heap2->rootList = nullptr; heap2->minNode = nullptr; heap2->nodeCount = 0; }
        return heap2; 
    }
    if (!heap2 || heap2->nodeCount == 0) { 
        if (heap1) { heap1->rootList = nullptr; heap1->minNode = nullptr; heap1->nodeCount = 0; }
        return heap1; 
    }

    MinFibHeap *newHeap = new MinFibHeap();
    newHeap->nodeCount = heap1->nodeCount + heap2->nodeCount;
    newHeap->rootList = heap1->rootList;

    newHeap->minNode = (heap1->minNode->key < heap2->minNode->key) ? heap1->minNode : heap2->minNode;

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
    heap1->minNode = nullptr;
    heap1->nodeCount = 0;
    heap2->rootList = nullptr;
    heap2->minNode = nullptr;
    heap2->nodeCount = 0;

    return newHeap;
}