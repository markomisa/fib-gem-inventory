#ifndef NODE_H
#define NODE_H

typedef struct Node {
    int key, degree;
    Node* parent;
    Node* child;
    Node* left;
    Node* right;
    
    // Constructor
    Node(int k) : key(k), degree(0), parent(nullptr), child(nullptr), left(this), right(this) {}
} Node;

#endif // NODE_H